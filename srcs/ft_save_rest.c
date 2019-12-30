/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_rest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 17:03:04 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:03:06 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_save_rest(char *str1, char *str2)
{
	int i;
	int a;
	char*dest;

	i = 0;
	a = 0;
	while (str1[i])
		i++;
	while (str2[a])
		a++;
	if (!(dest = malloc(a + i + 1)))
		return (0);
	i = -1;
	while (str1[++i])
		dest[i] = str1[i];
	a = -1;
	while (str2[++a])
		dest[i++] = str2[a];
	dest[i] = '\0';
	free(str1);
	return (dest);
}
