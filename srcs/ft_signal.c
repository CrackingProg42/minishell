/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:59:04 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:54:35 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigquit(void)
{
	ft_putstr("\b\b  \b\bquit\n");
	if (g_child > 0)
		kill(g_child, SIGINT);
}

void	ft_sigdump(void)
{
	ft_putstr("\b\b  \b\bI dumping this shit\n");
	if (g_child > 0)
		kill(g_child, SIGQUIT);
}
