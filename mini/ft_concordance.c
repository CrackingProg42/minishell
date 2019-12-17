/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concordance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:55:41 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/17 11:21:01 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_concordance2(char *str, char **envp, int mode)
{
	if (ft_cmp(str, "echo")) 
	{
		mode ? ft_echo(str, envp) : 0;
		return (0);
	}
	if (ft_strneedel(str, "cd")) 
	{
		return (0);
	}
	if (ft_strneedel(str, "pwd")) 
	{
		return (0);
	}
	while (*str == ' ')
		str++;
	return (*str == '\0' ? 0 : 1);
}

int		ft_concordance(char *str, char ***envp, int mode)
{
	if (ft_cmp(str, "export"))
	{
		*envp = ft_export(str, *envp);
		return (2);
	}
	if (ft_cmp(str, "unset")) 
	{
		return (2);
	} 
	if (ft_cmp(str, "env"))
		return (ft_env(*envp));
	if (ft_concordance2(str, *envp, mode))
	 	return(ft_invalidcmd(str, 0, *envp));
	 return (0);
}
