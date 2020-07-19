/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 11:57:50 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/18 17:55:59 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_token_quote(char *token)
{
	int		i;
	int		j;
	int		prev_is_backslash;
	char	*final_token;
	char	*tmp;
	t_quotes	quote;

	quote.q = -1;
	quote.dq = -1;
	i = 0;
	j = 0;
	prev_is_backslash = 0;
	if (!(final_token = (char*)malloc(sizeof(char) * ft_strlen_etokens(token))))
		return (NULL);
	while (token[i])
	{
		if (!prev_is_backslash)
		{
			token[i] == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
			token[i] == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
			if (token[i] == '\\' && token[i + 1])
			{
				prev_is_backslash = 1;
				i++;
			}
			else if (quote.q == -1 && token[i] == '$' && token[i + 1] && (ft_isalnum(token[i + 1]) || token[i + 1] == '?'))
			{
				tmp = final_token;
				if (!(final_token = expand_env(token, final_token, &i, &j)))
					return (NULL);
				free(tmp);
				if (!final_token)
					return(ft_strdup(""));
				if (!final_token[0])
				{
					return (final_token);
				}
			}
			else
			{
				final_token[j] = token[i];
				j++;
				i++;
			}
		}
		else
		{
			prev_is_backslash = 0;
			if (!is_specialchar_dquote(token[i]) && quote.dq == 1)
				final_token[j++] = '\\';
			final_token[j] = token[i];
			j++;
			i++;
		}
	}
	final_token[j] = '\0';
	return (final_token);
}

void	*get_final_token(void *content)
{
	char	*str;

	str = ((char*)content);
	str = expand_token_quote(str);
	str = remove_quotes(str);
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

t_list	*expand_tokens(t_list *token_list)
{
	t_list	*expanded_list;
	t_list	*tmp_list;
	
	tmp_list = token_list;
	expanded_list = ft_lstfilter(&tmp_list, get_final_token, free);
	return (expanded_list);
}
