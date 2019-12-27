/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:06:19 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/27 10:27:02 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_minus(char *str)
{
	free(str);
	return (-1);
}

int 	ft_free(char *str)
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
