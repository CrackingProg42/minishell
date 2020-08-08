/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 14:37:03 by franciszer        #+#    #+#             */
/*   Updated: 2020/08/08 16:08:40 by qfeuilla         ###   ########.fr       */
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

int		contain_redir(char **argv)
{
	int		i;
	int		type;

	i = 0;
	while (argv[i])
	{
		if ((type = is_redir(argv[i])))
			return (1);
		i++;
	}
	return (0);
}

t_list	*do_redir(char ***argv)
{
	t_redirection	*redir;

	redir = (t_redirection*)malloc(sizeof(t_redirection));
	*redir = stock_redir(*argv);
	if (redir_error(*redir))
	{
		free(redir);
		return (NULL);
	}
	cmd_to_rafter(argv);
	return (ft_lstnew(redir));
}

int		free_redir_lst(t_list **lst, int ret)
{
	ft_lstclear(lst, free);
	return (ret);
}

int		contain_putfile(t_list *redirs)
{
	t_list			*nav;
	t_redirection	red;

	nav = redirs;
	while (nav)
	{
		red = *(t_redirection*)nav->content;
		if (red.putendfile || red.putfile)
			return (1);
		nav = nav->next;
	}
	return (0);
}

int		execute_preprocess_redirs(char ***argv, t_list **redirs)
{
	t_list		*tmp;

	while (contain_redir(*argv))
	{
		if (!(tmp = do_redir(argv)))
			return (1);
		ft_lstadd_back(redirs, tmp);
	}
	return (0);
}

int		execute_redirs(int (*fd)[2], int *save, t_list *redirs)
{
	t_list		*nav;

	nav = redirs;
	while (nav)
	{
		if (redirection(*(t_redirection*)nav->content, fd, save) == -1)
			return (file_not_found(*(t_redirection*)nav->content));
		nav = nav->next;
	}
	return (0);
}

int		minishell_launch(char **argv, int *save, int last)
{
	pid_t			pid;
	int				fd[2];
	t_int2			save_last;
	t_list			*redirs;

	if (pipe(fd) < 0)
		return (0);
	if (!(redirs = do_redir(&argv)))
		return (1);
	if (execute_preprocess_redirs(&argv, &redirs))
		return (free_redir_lst(&redirs, 1));
	if (preprocess_minishell(&argv) || execute_redirs(&fd, save, redirs))
		return (free_redir_lst(&redirs, 1));
	save_last.a = *save;
	save_last.b = last;
	if (!(pid = fork()))
		child(save_last, contain_putfile(redirs), &argv, fd);
	else if (pid < 0)
		ft_perror(ERR_PID);
	else
		parent(&pid, save, fd);
	return (free_redir_lst(&redirs, 1));
}
