/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:54:05 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:56:57 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		compare(char str, char charset)
{
	if (str == charset)
		return (1);
	return (0);
}

int		nbcut(char *str, char charset)
{
	int count;
	int i;
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	i = -1;
	count = 0;
	while (str[++i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (dquote == 1 && quote == 1)
		{
			if (!compare(str[i], charset) && i == 0)
				count++;
			else if (compare(str[i], charset) && str[i + 1] != '\0')
				if (!compare(str[i - 1], charset))
					count++;
		}
	}
	return (count);
}

char	*asign(char *str, char charset, int *i, int b)
{
	int a;
	char*dest;
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	a = -1;
	while (str[++a + *i])
	{
		str[a + *i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[a + *i] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (dquote != -1 && quote != -1 && compare(str[a + *i], charset))
			break ;
	}
	if (!(dest = malloc(sizeof(char) * (a + 1))))
		return (0);
	while (b < a)
	{
		dest[b++] = str[*i];
		*i = *i + 1;
	}
	dest[b] = '\0';
	return (dest);
}

char	**ft_free_split(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (0);
}

char	**ft_split(char *str, char charset)
{
	int ncut;
	int i;
	int a;
	char**dest;

	i = -1;
	a = 0;
	ncut = nbcut(str, charset);
	if (!(dest = malloc(sizeof(*dest) * (ncut + 13))))
		return (0);
	while (str[++i])
	{
		if (!(dest[a] = asign(str, charset, &i, 0)))
			return (ft_free_split(dest));
		if (dest[a][0] == '\0')
			free(dest[a]);
		else
			a++;
		if (str[i] == '\0')
			break ;
	}
	dest[a] = 0;
	return (dest);
}
