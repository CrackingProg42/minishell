/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:10:26 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/22 14:36:24 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_printf("\nQuit (core dumped)\n");
		g_exit_status = 131;
		print_prompt();
	}
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\b\b\b\b\n");
		print_prompt();
	}
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
}
