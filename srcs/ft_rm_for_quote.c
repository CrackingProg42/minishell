/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_for_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:05:00 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:53:11 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rm_split_quote(char **str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] = ft_rm_quote(str[i])))
			return ;
	}
}

char	*ft_rm_quote(char *str)
{
	if (*str == '\'')
		return (ft_strtrim(str, "\'"));
	if (*str == '\"')
		return (ft_strtrim(str, "\""));
	return (str);
}
