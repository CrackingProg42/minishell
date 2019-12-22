/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 22:41:08 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/22 21:34:05 by QFM              ###   ########.fr       */
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
