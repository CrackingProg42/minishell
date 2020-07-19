/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:04:43 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/18 17:56:53 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char		*new;
	char		*tmp;
	int			i;
	t_quotes	quote;

	i = -1;
	quote.q = -1;
	quote.dq = -1;
	new = ft_strdup(str);
	while (new[++i]) 
	{
		new[i] == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
		new[i] == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
		if ((new[i] == '\'' && quote.dq == -1) || (new[i] == '\"' && quote.q == -1)) {
			tmp = &new[i + 1];
			new[i] = '\0';
			new = ft_strjoin_free(&new[0], tmp);
			i = i - 1;
		}
	}
	return (new);
}

int		is_specialchar_dquote(char c)
{
	if (c == '\\' || c == '$' || c == '\"')
		return (1);
	else
		return (0);
}

size_t	ft_strlen_etokens(char *s)
{
	int		i;
	size_t	maxlen;
	size_t	evar_count;
	
	i = 0;
	maxlen = 0;
	evar_count = 0;
	while (g_env[i])
	{
		if (ft_strlen(g_env[i]) > maxlen)
			maxlen = ft_strlen(g_env[i]);
		i++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			evar_count++;
		i++;
	}
	return (ft_strlen(s) + (evar_count * maxlen) + 1);
}
