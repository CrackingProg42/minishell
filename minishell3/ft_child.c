/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 13:13:15 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/13 14:48:10 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_child(char **envp)
{
	char *str;
	int	status;

	signal(SIGQUIT, ft_sigquit);
	while (1)
	{
		ft_home();
		if (get_next_line(0 ,&str) == -1)
				exit (-1);
		if (ft_check_quote(str))
			str = ft_get_str(str, 1, 1);		
		if ((g_child = fork()) == 0)
			ft_fonction(str, envp);
		waitpid(g_child,&status,0);
	}
	exit (0);
}
