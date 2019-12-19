/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:22:21 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/19 10:47:39 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cut_pipe(char *str, char ***envp)
{
	char **src;

	if (!(src = ft_split(str, '|')))
		return (1);
	if (ft_fork(src, envp))
		return (ft_free_2d(src));
	ft_free_2d(src);
	free(str);
	return (0);
}
