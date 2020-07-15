/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 14:37:03 by franciszer        #+#    #+#             */
/*   Updated: 2020/07/15 12:04:51 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigtest(int sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
}
int		minishell_launch(char **argv, int *save)
{
	pid_t	pid;
	char	*tmp;
	int		builtin_id;
	int		my_pipe[2];

	if(pipe(my_pipe) == -1) 
	{
		return (1);
	}
	dup2(*save, 0); // set last pipe output to input for thic command
	dup2(my_pipe[1], 1);
	if ((builtin_id = is_builtin(argv[0])) >= 0)
		g_exit_status = launch_builtin(builtin_id, argv);
	else if (builtin_id == -2)
		return (-1);
	if (builtin_id != -1)
		return (1);
	if (!(tmp = search_path(argv[0])))
	{
		ft_perror(ERR_UNKNOWN_COMMAND);
		return (1);
	}
	free(argv[0]);
	argv[0] = tmp;
	if (!(pid = fork()))
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_DFL);
		close(my_pipe[0]);
		if (execve(argv[0], argv, g_env) == -1)
			ft_perror(ERR_EXECVE);
	}
	else if (pid < 0)
		ft_perror(ERR_PID);
	else
	{
		waitpid(pid, &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else if (WIFSIGNALED(g_exit_status))
		{
			g_p_stop_sig = 1;
			if (WTERMSIG(g_exit_status) == SIGINT)
				g_exit_status = 130;
			if (WTERMSIG(g_exit_status) == SIGQUIT)
				g_exit_status = 131;
		}
		else
			g_exit_status = 0;
		
	}
	close(my_pipe[1]);
	*save = my_pipe[0];
	return (1);
}
