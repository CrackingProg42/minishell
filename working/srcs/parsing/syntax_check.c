/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 18:43:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/19 18:04:34 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	check_quotes(char *cmd) {
	int				i;
	t_quotes		quote;

	quote.q = -1;
	quote.dq = -1;
	i = -1;
	while (cmd[++i]) 
	{
		cmd[i] == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
		cmd[i] == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
	}
	if (quote.q == -1 && quote.dq == -1)
		return (1);
	return (0);
}

int		tokens_syntax_check(t_list *token_list)
{
	t_list	*nav;
	char	*str;

	nav = token_list;
	while (nav)
	{
		str = (char*)nav->content;
		if (!ft_strlen(str) || (isQuote(str[0]) && ft_strlen(str) == 1) ||\
			!check_quotes(str))
			return (0);
		nav = nav->next;
	}
	return (1);
}

int		pipes_syntax_check(t_list *token_list)
{
	if (ft_lstlen(token_list) == 1 && !ft_strncmp(last_token(token_list), "|", 2))
		return (0);
	return (1);
}

