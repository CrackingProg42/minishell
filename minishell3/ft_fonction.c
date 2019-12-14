/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 12:48:38 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/13 15:18:09 by paszhang         ###   ########.fr       */
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


int		ft_fonction(char *str, char ** envp)
{
	char **src;
	int i;

	i = -1;
	src = ft_split(str, ';');
	while (src[++i])
		if (!ft_concordance(src[i], envp))
					ft_invalidcmd(src[i], 0, envp);
	exit (0);
}


