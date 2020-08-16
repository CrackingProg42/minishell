/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:27:21 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/16 11:22:57 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ftoken_len(char *tk)
{
	int			i;
	int			pb;
	t_quotes	qt;
	size_t		len;

	i = 0;
	pb = 0;
	qt.q = -1;
	qt.dq = -1;
	len = 0;
	while (tk[i])
	{
		tk[i] == '\"' && qt.q == -1 && !pb ? qt.dq *= -1 : 0;
		tk[i] == '\'' && qt.dq == -1 && (!pb || qt.q == 1) ? qt.q *= -1 : 0;
		if (qt.q == -1 && qt.dq == -1 && !pb)
		{
			if (tk[i] == ' ')
				return(i);
			if ((len = token_len_special(&tk[i])))
			{
				if (i == 0)
					return (len);
				return (i);
			}
		}
		if (tk[i] == '\\' && pb == 0 && tk[i + 1] && qt.q == -1 && ++i)
			pb = 1;
		else
		{
			i++;
			pb = 0;
		}
	}
	return (i);	
}

size_t	token_len_special(char *tok_s)
{
	if (tok_s[0] == '>' && tok_s[1] && tok_s[1] == '>')
		return (2);
	else if (*tok_s == '|' || *tok_s == '>' || *tok_s == '<' ||
			*tok_s == ';')
		return (1);
	return (0);
}
