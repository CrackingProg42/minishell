/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:59:04 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/27 12:12:32 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	ctrl + \ = 28
*/

void	ft_sigquit()
{
	printf("\b\b  \b\bquit\n");
	if (g_child > 0)
	{	
		kill(g_child, SIGINT);
	}
}

void	ft_sigdump()
{
	printf("\b\b  \b\bI dumping this shit\n");
	if (g_child > 0)
	{	
		kill(g_child, SIGQUIT);
	}
}

/*
**	ctrl + c = 3
**  fleche gauche = 27 91 68 
**  fleche droite = 27 91 67
**	fleche bas = 27 91 66 
	fleche haut = 27 91 65
**	home = 27 91 72
** end = 27 91 70
** del = 27 91 51
**
**
**
**
**
*/

