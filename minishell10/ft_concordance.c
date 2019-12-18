/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concordance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:55:41 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/17 19:31:50 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_printable(char *str, char **envp)
{
	if (ft_cmp(str, "env"))
		return (g_dollar = ft_env(envp));
	if (ft_cmp(str, "echo")) 
		return (g_dollar = ft_echo(str, envp));
	if (ft_cmp(str, "pwd")) 
	{
		str = getcwd(NULL,0);
		ft_printf("%s\n",str);
		free(str);
		return (g_dollar = 0);
	}
	if (ft_cmp(str, "$?"))
	{
		str[0] = g_dollar + '0';
		str[1] = '\0';
		return ((g_dollar = ft_invalidcmd(str, 0, envp)));
	}
	if (!ft_path(str, envp))
		return (g_dollar = 0);	
	while (*str == ' ')
		str++;
	if (*str != '\0')
	{
		ft_invalidcmd(str, 0, envp);
		exit (-1);
	}
	return (0);
}

int		ft_concordance(char *str, char ***envp)
{
	if (ft_cmp(str, "cd")) 
		return (g_dollar = ft_cd(str, *envp));
	if (ft_cmp(str, "export"))
		return (!(int)(*envp = ft_export(str, *envp)));
	if (ft_cmp(str, "unset")) 
		return (g_dollar = ft_unset(str, *envp));
	if (ft_cmp(str, "exit")) 
		exit(0);
	return (1);
}
