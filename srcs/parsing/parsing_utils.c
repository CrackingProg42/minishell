/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:28:17 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/08 11:57:50 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int		is_special_char(char *s)
{
	if (*s == '<' || *s == '>' || *s == ';'
	|| *s == '|' || !ft_strncmp(">>", s, 2))
		return (1);
	else
		return (0);
}
