/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:59:04 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/13 14:54:18 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dummit(int a)
{
	
}


void	ft_sigquit(int a)
{
	if (g_child > 0)
		kill(g_child, SIGTERM);
}

void	ft_sig(int a)
{
	if (g_pid > 0)
	{
		write(1, "\b\b  \b\b",6);
		kill(g_pid, SIGTERM);
		write(1, "\n",1);
	}
}
