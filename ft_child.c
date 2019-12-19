/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:29:57 by qfeuilla          #+#    #+#             */
/*   Updated: 2019/12/19 15:44:18 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child2(int pipefd[2], char ***envp)
{
	
}

int		ft_child(char **envp)
{
	int		status;
	int		pipefd[2];

	while (1)
	{
		if (pipe(pipefd) == -1)
			return (1);
		if ((g_pid = fork()) == 0)
		{

		}
		waitpid(g_pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 255)
			return (0);
		if (g_pid == 0)
		{
			close (pipefd[0]);
			close (pipefd[1]);
			continue ;
		}
		ft_child2(pipefd, &envp);
	}
}