/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:01:33 by qfeuilla          #+#    #+#             */
/*   Updated: 2019/12/19 15:29:44 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	g_dollar = 0;
	signal(SIGQUIT, ft_sigquit);
	signal(SIGINT, ft_sig);
	ft_child(envp);
	return (0);
}