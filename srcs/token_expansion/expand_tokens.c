/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 11:57:50 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/08 17:03:20 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_bzero(char **final_token, int index)
{
	(*final_token)[index] = '\0';
	return (*final_token);
}

int		is_quote_only(char *tk)
{
	if (ft_strlen(tk) == 2 && (!ft_strncmp(tk, "\"\"", 3)
		|| !ft_strncmp(tk, "\'\'", 3)))
		return (1);
	return (0);
}

char	*expand_token_quote(char *tk, s_expand_tk_dt d)
{
	if (is_quote_only(tk))
		return (ft_strdup("\33\127"));
	if (!(d.final_token = init_expand(&d.qt, &d.ij, &d.pb, tk)))
		return (NULL);
	while (tk[d.ij.a])
	{
		tk[d.ij.a] == '\'' && d.qt.dq == -1 && (!d.pb || d.qt.q == 1)
				? d.qt.q *= -1 : 0;
		if (!d.pb || d.qt.q == 1)
			if (if_loop(tk, &d.ij, &d.qt, &d.pb))
				d.final_token = d.final_token;
			else if (elif_test(tk, d.qt, d.ij))
			{
				d.tmp = d.final_token;
				if (!(d.final_token = eev(tk, d.final_token, &d.ij.a, &d.ij.b)))
					return (NULL);
				if (elif_loop(&d.final_token, &d.tmp))
					return (d.final_token);
			}
			else
				d.final_token[d.ij.b++] = tk[d.ij.a++];
		else if (!(d.pb = 0))
			else_loop(tk, &d.final_token, &d.ij, &d.qt);
	}
	return (add_bzero(&d.final_token, d.ij.b));
}

void	*get_final_token(void *content)
{
	char			*str;
	s_expand_tk_dt	d;

	d.qt.q = -1;
	str = ((char*)content);
	str = expand_token_quote(str, d);
	if (!str || !str[0])
		return (NULL);
	return (str);
}

void	clear_token(t_list **token_list)
{
	t_list *nav;
	t_list **tmp;

	nav = *token_list;
	while (nav)
	{
		if (!nav->content)
		{
			tmp = &nav;
			(*tmp) = nav->next;
		}
		nav = nav->next;
	}
}

t_list	*expand_tokens(t_list *token_list)
{
	t_list	*expanded_list;
	t_list	*tmp_list;

	tmp_list = token_list;
	expanded_list = ft_lstfilter(&tmp_list, get_final_token, free);
	clear_token(&expanded_list);
	return (expanded_list);
}
