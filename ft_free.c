/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:06:19 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/22 21:34:07 by QFM              ###   ########.fr       */
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

char 	*ft_free_null(char **str)
{
	free(*str);
	return (NULL);
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
