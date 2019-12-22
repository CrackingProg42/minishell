/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concordance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:55:41 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/22 21:34:32 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_printable(char *str, char **envp)
{
	if (ft_cmp(str, "env"))
		exit (ft_env(envp));
	if (ft_cmp(str, "echo")) 
		exit (ft_echo(str, envp));
	if (ft_cmp(str, "pwd")) 
	{
		str = getcwd(NULL,0);
		ft_printf("%s\n",str);
		free(str);
		exit (0);
	}
	if (ft_cmp(str, "$?"))
		exit ((ft_error_dollar()));
	ft_path(str, envp);
	while (*str == ' ')
		str++;
	if (*str != '\0')
		exit (127);
	exit (0);
}

int		ft_concordance(char *str, char ***envp)
{
	if (ft_cmp(str, "cd")) 
		return (g_d = ft_cd(str, *envp));
	if (ft_cmp(str, "export"))
		return (!(int)(*envp = ft_export(str, *envp)));
	if (ft_cmp(str, "unset")) 
		return (g_d = ft_unset(str, *envp));
	if (ft_cmp(str, "exit")) 
		exit(0);
	return (1);
}
