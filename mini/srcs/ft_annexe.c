/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_annexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:48:37 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/17 14:58:00 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_lenght_to_cara(char *str, char cara)
{
	int quote;
	int dquote;
	int i;

	dquote = 1;
	quote = 1;
	i = 0;
	while (str[i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1: 0;
		if (str[i] == cara  && quote == 1 && dquote == 1)
			break ;
		i++;
	}
	return (i);
}

char 	*ft_dup_to_space(char *str)
{
	char *dest;
	int i;
	int lenght;

	lenght = ft_lenght_to_cara(str, ' ');
	if (!(dest = malloc(lenght + 1)))
		return (0);
	i = 0;
	while (i < lenght)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


void	ft_putstrfd(int fd, char *str)
{
	while(*str)
		write(fd, str++, 1);
}

int		ft_cmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while(str1[i] == ' ')
		i++;
	while(str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return (str2[i] == '\0' && (str1[i] == '\0' || str1[i] == ' ')) ? 1 : 0;
}

int		ft_cmp_to_cara(char *str1, char *str2, char c)
{
	int quote;
	int dquote;
	int i;

	dquote = 1;
	quote = 1;
	i = 0;
	while(str1[i] == str2[i] && str1[i] && str2[i])
	{
		str1[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str1[i] == '\"' && quote == 1 ? dquote *= -1: 0;
		if (str1[i] == c  && quote == 1 && dquote == 1)
			break ;
		i++;
	}
	return ((str1[i] == c && str2[i] == c) ? 1 : 0);
}

int		ft_cmp_tospace(char *str1, char *str2)
{
	int i;

	i = 0;
	while(str1[i] && str2[i] && str2[i] != ' ' && str2[i] != '\"')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (str2[i] == ' ' || str2[i] == '\"' || str2[i] == '\0' ) ? 1 : 0;
}

char	*ft_strneedel(char *src, char *need)
{
	int i;
	int a;

	if (src == NULL || need == NULL)
		return (0);
	i = 0;
	while (src[i])
	{
		a = 0;
		while(src[i + a] == need[a] && need[a])
			a++;
		if (need[a] == '\0' && (src[i + a] == '\0' || src[i + a] == ' '))
			return (&src[i + a]);
		i++;
	}
	return (0);
}

