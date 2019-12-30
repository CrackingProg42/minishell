/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jump_to_cara.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 11:22:31 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:20:03 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_jump_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' && str[i])
		i++;
	return (i);
}

int		ft_jump_first_word(char *str)
{
	int i;
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	i = -1;
	while (str[++i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (dquote == 1 && quote == 1 && str[i] == ' ')
			break ;
	}
	return (i);
}
