/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:06:19 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:18:31 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_free_null(char *str)
{
	free(str);
	return (NULL);
}

int		ft_free_minus(char *str)
{
	free(str);
	return (-1);
}

int		ft_free(char *str)
{
	free(str);
	return (1);
}

int		ft_free_2tab(char **str1, char **str2, int ret)
{
	ft_free_2d(str1);
	ft_free_2d(str2);
	return (ret);
}

int		ft_free_2d(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (1);
}
