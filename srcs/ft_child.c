/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 13:13:15 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:14:55 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child2(int pipefd[2], t_env *env)
{
	char *str;

	if (!(str = ft_get_str(NULL, 1, 1, pipefd[0])))
		exit(-1);
	ft_cut_comma(str, env);
	free(str);
	ft_close_pipe(pipefd);
}

int		ft_child(t_env *env)
{
	int	status;
	int	pipefd[2];

	while (1)
	{
		g_child = 0;
		if (pipe(pipefd) == -1)
			return (1);
		if ((g_pid = fork()) == 0)
			exit(ft_get_cmd(pipefd));
		waitpid(g_pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 255)
			return (0);
		if (g_pid == 0)
		{
			ft_close_pipe(pipefd);
			continue ;
		}
		ft_child2(pipefd, env);
	}
	return (0);
}
