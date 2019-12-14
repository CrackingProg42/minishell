/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stupid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 22:41:08 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/15 00:03:00 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_stupid(int pipe)
{
	char *save;

	save = malloc(1);
	*save = '\0';
	if (!(save = ft_get_str(save, 1, 1, 0)))
		return (-1);
	while(*save)
		write(pipe, save++, 1);
	write(pipe, "\n",1);
	return (0);
}


