/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 18:43:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/24 22:46:31 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_quotes(char *cmd)
{
	int				i;
	t_quotes		quote;
	int				p_back;

	p_back = 0;
	quote.q = -1;
	quote.dq = -1;
	i = -1;
	while (cmd[++i])
	{
		cmd[i] == '\'' && quote.dq == -1 &&
			(!p_back || quote.q == 1) ? quote.q *= -1 : 0;
		cmd[i] == '\"' && quote.q == -1 && !p_back ? quote.dq *= -1 : 0;
		if (cmd[i] == '\\' && p_back == 0)
			p_back = 1;
		else
			p_back = 0;
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
		if (!ft_strlen(str) || (is_quote(str[0]) && ft_strlen(str) == 1) ||\
			!check_quotes(str))
			return (0);
		nav = nav->next;
	}
	return (1);
}

int		pipes_syntax_check(t_list *token_list)
{
	if (ft_lstlen(token_list) == 1 &&
		!ft_strncmp(last_token(token_list), "|", 2))
		return (0);
	return (1);
}
