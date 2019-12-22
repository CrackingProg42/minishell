/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:59:04 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/20 10:01:13 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	ctrl + \
*/

void	ft_sigquit()
{
/*	if (g_pid > 0)
		write(1, "\b\b  \b\b",6);
	if (g_child > 0)
		kill(g_child, SIGTERM);*/
}

/*
**	ctrl + c
*/

void	ft_sig()
{
	if (g_pid > 0)
	{
		write(1, "\b\b  \b\b",6);
		kill(g_pid, SIGTERM);
		g_pid = 0;
		write(1, "\n",1);
	}
}
