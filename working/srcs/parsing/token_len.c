/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:27:21 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/20 16:16:58 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	token_len(char *tokenStart)
{
	size_t	i;
	size_t	len;
	int		prev_is_backslash;
	

	i = 0;
	len = 0;
	prev_is_backslash = 0;
	while (tokenStart[i])
	{
		if (((is_quote(tokenStart[i]) || is_special_char(&tokenStart[i])) || ft_isspace(tokenStart[i]) )&& !prev_is_backslash)
		{
			if (tokenStart[i] == '\'')
				return (len + token_len_s_quote(&tokenStart[i]));
			if (tokenStart[i] == '\"')
				return (len + token_len_s_quote(&tokenStart[i]));
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

size_t	token_len_s_quote(char *tokenStart)
{
	size_t	i;
	
	i = 1;
	while (tokenStart[i])
	{
		if (tokenStart[i] == '\'')
		{
			if (tokenStart[i + 1] && !is_special_char(&tokenStart[i + 1]) && tokenStart[i + 1] != ' ') 
			{
				if (*tokenStart == '\'' && ++i)
					return (i + token_len_s_quote(&tokenStart[i]));
				else if (*tokenStart == '\"' && ++i)
					return (i + token_len_d_quote(&tokenStart[i]));
				else if (++i)
					return (i + token_len(&tokenStart[i]));
			}
			else
				return (++i);
		}
		i++;
	}
	return (i);
}

size_t	token_len_d_quote(char *tokenStart)
{
	size_t	i;
	int		prev_is_backslash;
	
	i = 1;
	prev_is_backslash = 0;
	while (tokenStart[i])
	{
		if (tokenStart[i] == '\"' && !prev_is_backslash) 
		{
			if (tokenStart[i + 1] && !is_special_char(&tokenStart[i + 1]) && tokenStart[i + 1] != ' ') 
			{
				if (*tokenStart == '\'' && ++i)
					return (i + token_len_s_quote(&tokenStart[i]));
				else if (*tokenStart == '\"' && ++i)
					return (i + token_len_d_quote(&tokenStart[i]));
				else if (++i)
					return (i + token_len(&tokenStart[i]));
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
