/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 14:37:03 by franciszer        #+#    #+#             */
/*   Updated: 2020/07/22 17:19:20 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigtest(int sig)
{
	if (sig == SIGINT)
		g_exit_status = 130;
}

char	**copy_argv(char **argv)
{
	int		i;
	int		j;
	char	**argv2;

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
	pid_t			pid;
	int				ret;
	int				fd[2];
	t_redirection	redir;
	t_int2			save_last;

	if (pipe(fd) < 0)
		return (0);
	redir = stock_redir(argv);
	if (redir_error(redir))
		return (1);
	cmd_to_rafter(&argv);
	if ((ret = preprocess_minishell(&argv)))
		return (ret);
	redirection(redir, &fd, save);
	save_last.a = *save;
	save_last.b = last;
	if (!(pid = fork()))
		child(save_last, redir, &argv, fd);
	else if (pid < 0)
		ft_perror(ERR_PID);
	else
		parent(&pid, save, fd);
	return (1);
}
