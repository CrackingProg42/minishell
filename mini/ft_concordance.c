/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concordance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:55:41 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/16 21:06:16 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*ft_concordance2(char *str, char **envp, int mode)
{
	char *ret;

	(ret = ft_strneedel(str, "echo")) && mode ? ft_echo(str, envp) : 0;
	if (!ret)
	{
		while (*str == ' ')
			str++;
		return (*str == '\0' ? str : 0);
	}
	return (ret);
}

int		ft_concordance(char *str, char **envp, int mode)
{
	 if (!ft_concordance2(str, envp, mode))
	 {
	 	ft_invalidcmd(str, 0, envp);
		return (1);
	 }
	 return (0);
}
