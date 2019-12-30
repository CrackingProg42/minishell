/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patchabsolut.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 17:20:17 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:23:24 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_found_path(char **envp, char *need)
{
	char*path;
	int i;

	i = 0;
	while (envp[i])
		if ((path = ft_strneedel_cara(envp[i++], need, '=')))
			break ;
	if (!path)
		return (0);
	path++;
	return (path);
}

char	*ft_prepare_str(char *str)
{
	if (*str != '/')
		if (!(str = ft_join("/", str)))
			return (0);
	return (str);
}

void	ft_test_path(char *str, char **envp)
{
	char **arg;

	if (!(arg = ft_split(str, ' ')))
		return ;
	ft_rm_split_quote(arg);
	execve(arg[0], &arg[0], envp);
}

int		ft_path(char *str, char **envp, int i)
{
	char*path;
	char**splitpath;
	char**arg;

	ft_test_path(str, envp);
	if (!(path = ft_found_path(envp, "PATH")))
		return (1);
	if (!(splitpath = ft_split(path, ':')))
		return (1);
	if (!(arg = ft_split(str, ' ')))
		return (ft_free_2d(splitpath));
	ft_rm_split_quote(arg);
	if (!(arg[0] = ft_prepare_str(arg[0])))
		return (1);
	path = arg[0];
	while (splitpath[i])
	{
		ft_rm_split_quote(arg);
		if (!(arg[0] = ft_join(splitpath[i++], path)))
			return (ft_free_2d(splitpath));
		ft_rm_split_quote(arg);
		execve(arg[0], &arg[0], envp);
		wait(NULL);
	}
	return (0);
}
