/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 11:18:29 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/08 15:47:12 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	modify_path(char *arg, char *var)
{
	t_list	*env_list;
	t_list	*nav;

	if (!(env_list = ft_argv_to_list(g_env)))
		return (1);
	nav = env_list;
	while (nav)
	{
		if (!ft_strncmp((char*)nav->content, (const char*)var, ft_strlen(var))
			&& ((char*)nav->content)[ft_strlen(var) - 1] == '=')
		{
			free(nav->content);
			if (!(nav->content = ft_strjoin(var, arg)))
				return (1);
		}
		nav = nav->next;
	}
	if (g_env_modified)
		free_argv(g_env, INT_MAX);
	else
		g_env_modified = 1;
	if (!(g_env = list_to_argv(env_list)))
		return (1);
	ft_lstclear(&env_list, free);
	return (0);
}

int			ft_go_home(char *current_dir)
{
	char	**new;
	char	*home;
	int		return_value;
	char	*check_home;

	if (!(check_home = get_env("HOME")))
		return (1);
	if (!ft_strncmp(check_home, current_dir, ft_strlen(current_dir) + 1))
		return_value = 0;
	else
	{
		if (!(new = malloc(sizeof(char*) * 3)))
			return (1);
		if (!(new[0] = ft_strdup("cd")))
			return (1);
		if (!(home = get_env("HOME")))
			return (1);
		new[1] = home;
		return_value = builtin_cd(new);
		free_argv(new, INT_MAX);
	}
	free(check_home);
	free(current_dir);
	return (return_value);
}

int			builtin_cd(char **args)
{
	char	*directory;

	if (!(directory = getcwd(NULL, 0)))
		return (1);
	if (!args[1])
		return (ft_go_home(directory));
	if (chdir(args[1]) < 0)
	{
		free(directory);
		ft_perror(strerror(errno));
		return (1);
	}
	else
	{
		if (modify_path(directory, "OLDPWD="))
			return (1);
		free(directory);
		if (!(directory = getcwd(NULL, 0)))
			return (1);
		if (modify_path(directory, "PWD="))
			return (1);
		free(directory);
	}
	return (0);
}
