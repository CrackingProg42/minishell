/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 13:13:15 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/15 00:05:39 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_child(char **envp)
{
	char *str;
	int	status;
	int pipefd[2];

	str = malloc (1);
	*str = '\0';
	while (1)
	{
		if (pipe(pipefd) == -1)
			return (1);
		if ((g_pid = fork()) == 0)
		{
			ft_home();
			if (ft_stupid(pipefd[1]) == -1)
				exit (-1);
			exit(0);
		}
		waitpid(g_pid, &status,0);
		if (WIFEXITED(status))
			if(WEXITSTATUS(status) == 255)
				return (0);
		if (g_pid == 0)
		{
			close (pipefd[1]);
			close (pipefd[0]);
			continue ;
		}
		if ((g_child = fork()) == 0)
		{
			if (!(str = ft_get_str(str, 1, 1, pipefd[0])))
				exit (-1);
			ft_fonction(str, envp, ';');
			exit(0);
		}
		wait(NULL);
		close (pipefd[1]);
		close (pipefd[0]);
	}
	exit (0);
}
