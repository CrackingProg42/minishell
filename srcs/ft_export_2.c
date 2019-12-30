/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 18:43:03 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 18:43:27 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_export(char *str, int lenght)
{
	int quote;
	int dquote;
	int i;

	dquote = 1;
	quote = 1;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '_' && str[i + 1] == '=')
		return (1);
	while (lenght-- && str[i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (str[i] == '=' && quote == 1 && dquote == 1)
		{
			if (i == 0 || str[i + 1] == ' ' || str[i + 1] == '\0')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int		ft_cmp_export(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return ((str1[i] == '=' && str2[i] == '\0') ? 1 : 0);
}

char	*ft_local(char *str, char **local)
{
	int i;

	i = 0;
	while (local[i])
	{
		if (ft_cmp_export(local[i], str))
			return (ft_strdup(local[i]));
		i++;
	}
	return (0);
}
