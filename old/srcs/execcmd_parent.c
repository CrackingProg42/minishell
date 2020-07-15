/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:00:52 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/03/05 15:18:01 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		execcd(char *cmd, char **env) {
	char **params;
	params = ft_split_with_quote(cmd, ' ');

	if (params[1]) {
		if (!params[2]) {
			chdir(params[1]);
		}
		else
			printf("error");
	}
	else {
		chdir(ft_get_env(env, "HOME"));
	}
	return (1);
}

int		execunset(char *cmd, char ***env, int a) {
	int		i;
	char 	**val;
	char 	**params;
	
	params = ft_split_with_quote(cmd, ' ');
	i = 0;
	printf("ok\n");
	while ((*env)[i]) {
		val = ft_split((*env)[i], '=');
		if (params[a] && ft_strlen(val[0]) == ft_strlen(params[a]) && !ft_strncmp(val[0], params[a], ft_strlen(val[0]))) {
			free_tab(val);
			printf("ok\n");
			while (((*env)[i] = (*env)[i + 1])) 
				i++;
			(*env)[i] = NULL;
			free((*env)[i]);
			return (0);
		}
		free_tab(val);
		i++;
	}
	return (1);
}

int		execexport(char *cmd, char ***env, int a) {
	int		len;
	char 	**val;
	char 	*es;
	char 	**params;
	char	*cm;
	char	**new;
	char	***tmp;

	params = ft_split_with_quote(cmd, ' ');
	val = ft_split(params[a], '=');
	cm = ft_strjoin("unset ", val[0]);
	execunset(cm, env, 1);
	free(cm);
	free_tab(val);
	es = ft_strdup(params[a]);
	len = ft_lstlen(*env);
	printf("len of env %d\n", ft_lstlen(params));
	tmp = env;
	new = (char **)malloc(sizeof(char*) * (len + 1));
	len = 0;
	while ((*env)[len]) {
		new[len] = ft_strdup((*env)[len]);
		len++;
	}
	new[len++] = es;
	new[len] = NULL;
	*env = new;
	// free tmp
	if (a == ft_lstlen(params) - 1)
		return (1);
	return (0);
}

int 	execcmd_parent(char *cmd, char ***env) {
	char *tmp;
	int len;
	int	ret;
	int a;

	a = 1;
	ret = 0;
	tmp = ft_strtrim(cmd, " ");
	len = ft_strlen(tmp);
	if (!ft_strncmp(tmp, "cd", 2))
		ret = execcd(tmp, *env);
	if (!ft_strncmp(tmp, "unset", 5))
		while (!(ret = execunset(tmp, env, a++)));
	if (!ft_strncmp(tmp, "export", 6))
		while (!(ret = execexport(tmp, env, a++)));
	free(tmp);
	return (ret);
}