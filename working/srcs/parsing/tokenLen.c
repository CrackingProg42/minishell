/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenLen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:27:21 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/17 21:34:59 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	tokenLen(char *tokenStart)
{
	size_t	i;
	size_t	len;
	int		prev_is_backslash;
	

	i = 0;
	len = 0;
	prev_is_backslash = 0;
	while (tokenStart[i])
	{
		if (((isQuote(tokenStart[i]) || isSpecialChar(&tokenStart[i])) || ft_isspace(tokenStart[i]) )&& !prev_is_backslash)
		{
			if (tokenStart[i] == '\'')
				return (len + tokenLenSQuote(&tokenStart[i]));
			if (tokenStart[i] == '\"')
				return (len + tokenLenSQuote(&tokenStart[i]));
			return (len);
		}
		if (tokenStart[i] == '\\')
			prev_is_backslash = 1;
		else
			prev_is_backslash = 0;
		i++;
		len++;
	}
	return (len);
}

size_t	tokenLenSQuote(char *tokenStart)
{
	size_t	i;
	
	i = 1;
	while (tokenStart[i])
	{
		if (tokenStart[i] == '\'')
		{
			if (tokenStart[i + 1] && !isSpecialChar(&tokenStart[i + 1]) && tokenStart[i + 1] != ' ') 
			{
				if (*tokenStart == '\'' && ++i)
					return (i + tokenLenSQuote(&tokenStart[i]));
				else if (*tokenStart == '\"' && ++i)
					return (i + tokenLenDQuote(&tokenStart[i]));
				else if (++i)
					return (i + tokenLen(&tokenStart[i]));
			}
			else
				return (++i);
		}
		i++;
	}
	return (i);
}

size_t	tokenLenDQuote(char *tokenStart)
{
	size_t	i;
	int		prev_is_backslash;
	
	i = 1;
	prev_is_backslash = 0;
	while (tokenStart[i])
	{
		if (tokenStart[i] == '\"' && !prev_is_backslash) 
		{
			if (tokenStart[i + 1] && !isSpecialChar(&tokenStart[i + 1]) && tokenStart[i + 1] != ' ') 
			{
				if (*tokenStart == '\'' && ++i)
					return (i + tokenLenSQuote(&tokenStart[i]));
				else if (*tokenStart == '\"' && ++i)
					return (i + tokenLenDQuote(&tokenStart[i]));
				else if (++i)
					return (i + tokenLen(&tokenStart[i]));
			}
			else
				return (++i);
		}
		if (tokenStart[i] == '\\')
			prev_is_backslash = 1;
		else
			prev_is_backslash = 0;
		i++;
	}
	return (i);
}

size_t	token_len_special(char *token_start)
{
	if (token_start[0] == '>' && token_start[1] && token_start[1] == '>')
		return (2);
	else if (*token_start == '|' || *token_start == '>' || *token_start == '<' ||
			*token_start == ';')
		return (1);
	return (0);
}
