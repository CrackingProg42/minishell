/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stupid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 22:41:08 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/16 12:25:30 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_cmd(int pipe)
{
	char *save;
	int i;

	i = 0;
	ft_home();
	if (!(save = ft_get_str(1, 1, 0)))
		return (-1);
	while(save[i])
		write(pipe, &save[i++], 1);
	free(save);
	write(pipe, "\n",1);
	return (0);
}
