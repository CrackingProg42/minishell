/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_annexe_quentin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:42:09 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/17 10:42:36 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_join(char *str1, char *str2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1))))
		return (NULL);
	while (str1[i])
		new[j++] = str1[i++];
	i = 0;
	while (str2[i])
		new[j++] = str2[i++];
	new[j] = '\0';
	return (new);
}
