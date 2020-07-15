/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execcmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:33:01 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/03/05 14:17:17 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	execenv(char *cmd, char **env) {
	int i;

	i = 0;
	// handle error of parse
	while (env[i]) {
		printf("%s\n", env[i++]); // use ft
	}
}

void	exececho(char *cmd, char **env) {
	int	nOption;
	char **params;
	int i;

	nOption = FALSE;
	params = ft_split_with_quote(cmd, ' ');
	if (params[1])
		nOption = (ft_strnstr(params[1], "-n", ft_strlen(cmd)) ? TRUE : FALSE);
	i = nOption ? 2 : 1;
	while (params[i])
		if (i > (nOption ? 2 : 1))
			printf(" %s", params[i++]);
		else
			printf("%s", params[i++]);
	if (!nOption)
		printf("\n");
	// ADD the $VAR handling
}

void	execpwd(char *cmd, char **env) {
	char cwd[4096];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s\n", cwd);
	}
}

void 	execcmd(char *cmd, char ***env) {
	char *tmp;
	int len;

	tmp = ft_strtrim(cmd, " ");
	len = ft_strlen(tmp);
	if (!ft_strncmp(tmp, "env", 3))
		execenv(tmp, *env);
	if (!ft_strncmp(tmp, "echo", 4))
		exececho(tmp, *env);
	if (!ft_strncmp(tmp, "pwd", 3))
		execpwd(tmp, *env);
	free(tmp);
	exit(0);
}