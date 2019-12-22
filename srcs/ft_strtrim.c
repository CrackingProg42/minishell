/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:16:02 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/16 14:12:32 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		ft_detectset(char c, char const *set)
{
	while (*set)
		if (*set == c)
			return (1);
		else
			set++;
	return (0);
}

char			*ft_strtrim(char *s1, char const *set)
{
	int	lenght;
	int	i;
	int a;
	char*dest;

	a = 0;
	lenght = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[lenght])
		lenght++;
	if (!(dest = malloc(sizeof(char) * (lenght + 1))))
		return (0);
	while (ft_detectset(s1[a], set) && s1[a])
		a++;
	lenght--;
	while (ft_detectset(s1[lenght], set) && lenght > a)
		lenght--;
	i = 0;
	while (a <= lenght && s1[a])
		dest[i++] = s1[a++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}
