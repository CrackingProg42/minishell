/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:19:51 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/14 16:53:17 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	int status;

	(void)ac;
	(void)av;
	g_child = 0;
	signal(SIGQUIT, ft_dummit); // ctrl + '\' 
	signal(SIGINT, ft_sig); // ctrl + c 
	while (1)
	{
		if ((g_pid = fork()) == 0)
			ft_child(envp);
		waitpid(g_pid, &status,0);
		if (WIFEXITED(status))
      		if(WEXITSTATUS(status) == 255)
				return (0);
	}
}

