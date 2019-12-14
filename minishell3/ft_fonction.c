/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 12:48:38 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/14 23:45:47 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*ft_concordance(char *str, char **envp)
{
	char *ret;

	(ret = ft_strneedel(str, "echo")) ? ft_echo(str, envp) : 0;
	if (!ret)
	{
		while (*str == ' ')
			str++;
		return (*str == '\0' ? str : 0);
	}
	return (ret);
}


int		ft_fonction(char *str, char ** envp, char cara)
{
	char **src;
	int i;

	i = -1;
	src = ft_split(str, cara);
	while (src[++i])
		if (cara == ';')
			ft_fonction(src[i], envp, '|');
		else if (!ft_concordance(src[i], envp))
					ft_invalidcmd(src[i], 0, envp);
	return (0);
}


