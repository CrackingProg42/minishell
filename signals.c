/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:10:30 by qfeuilla          #+#    #+#             */
/*   Updated: 2019/12/19 15:29:41 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit()
{
	if (g_pid > 0)
		write(1, "\b\b  \b\b", 6);
	if (g_child > 0)
		kill(g_child, SIGTERM);
}

void	sig()
{
	if (g_pid > 0)
	{
		write(1, "\b\b  \b\b",6);
		kill(g_pid, SIGTERM);
		g_pid = 0;
		write(1, "\n", 1);
	}
}