/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_annexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:48:37 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/14 22:41:56 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstrfd(int fd, char *str)
{
	while(*str)
		write(fd, str++, 1);
}
// for echo , so we know that it have echo at the beginning of the str and we don t care at what we have after 
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

int		ft_cmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while(str1[i] == ' ')
		i++;
	while(str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (str2[i] == '\0') ? 1 : 0;
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
		if (need[a] == '\0')
			return (&src[i + a]);
		i++;
	}
	return (0);
}

