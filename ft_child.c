/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 13:13:15 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/20 10:15:01 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child2(int pipefd[2], char ***envp)
{
	char *str;

	if (!(str = ft_get_str(1, 1, pipefd[0])))
		exit (-1);
	ft_cut_comma(str, envp);
	wait(NULL);
	free(str);
	ft_close_pipe(pipefd);
}
	
int		ft_child(char **envp)
{
	int	status;
	int pipefd[2];

	while (1)
	{
		g_child = 0;
		if (pipe(pipefd) == -1)
			return (1);
		if ((g_pid = fork()) == 0)
		{
			if (ft_get_cmd(pipefd[1]))
					exit (-1);
			exit(0);
		}
		waitpid(g_pid, &status,0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 255)
				return (0);
		if (g_pid == 0)
		{
			ft_close_pipe(pipefd);
			continue ;
		}
		ft_child2(pipefd, &envp);
	}
	return (0);
}
