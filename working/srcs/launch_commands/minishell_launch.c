/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 14:37:03 by franciszer        #+#    #+#             */
/*   Updated: 2020/07/17 15:51:56 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigtest(int sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
}

char 	**copy_argv(char **argv) {
	int i;
	int j;
	char **argv2;

	i = 0;
	j = -1;
	while (argv[i] != NULL)
		i++;
	argv2 = (char **)malloc(i * sizeof(char *));
	while (++j < i)
		argv2[j] = ft_strdup(argv[j]);
	return (argv2);
}

int		minishell_launch(char **argv, int *save, int last)
{
	pid_t	pid;
	char	*tmp;
	int		builtin_id;
	int		fd[2];
	t_redirection redir;

	if (pipe(fd) < 0)
		return (0);
	redir = stock_redir(table_to_string(argv));
	cmd_to_rafter(&argv);
	redirection(redir, &fd, save);
	g_exit_status = 0;
	if ((builtin_id = is_builtin_parent(argv[0])) >= 0)
		g_exit_status = launch_builtin_parent(builtin_id, argv);
	else if (builtin_id == -2)
		return (-1);
	if (builtin_id != -1)
		return (1);
	if (!(tmp = search_path(argv[0])))
	{
		g_exit_status = 127;
		ft_perror(ERR_UNKNOWN_COMMAND);
		return (1);
	}
	free(argv[0]);
	argv[0] = tmp;
	if (!(pid = fork()))
	{
		dup2(*save, 0);
		if (!last || redir.putfile || redir.putendfile)
			dup2(fd[1], 1);
		close(fd[0]);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_DFL);
		if ((builtin_id = is_builtin_child(argv[0])) >= 0) {
			g_exit_status = launch_builtin_child(builtin_id, argv);
			exit(g_exit_status);
		}
		else if (execve(argv[0], argv, g_env) == -1)
			ft_perror(ERR_EXECVE);
	}
	else if (pid < 0)
		ft_perror(ERR_PID);
	else
	{
		waitpid(pid, &g_exit_status, 0);
		*save = fd[0];
		close(fd[1]);
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
	return (1);
}
