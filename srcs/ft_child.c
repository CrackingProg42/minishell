/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 13:13:15 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/27 10:29:19 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child2(int pipefd[2], t_env *env)
{
	char *str;

	if (!(str = ft_get_str(1, 1, pipefd[0])))
		exit (-1);
	ft_cut_comma(str, env);
	free(str);
	ft_close_pipe(pipefd);
}
	
int		ft_child(t_env *env)
{
	int	status;
	int pipefd[2];
	struct termios termios1;
	struct termios termios2;
	
	tcgetattr(0,&termios1);
	tcgetattr(0,&termios2);
	termios1.c_cc[VMIN] = 1;
	termios1.c_lflag &= ~(ICANON | ECHO |ISIG| ECHOCTL);
	while (1)
	{
		g_child = 0;
		if (pipe(pipefd) == -1)
			return (1);
		if ((g_pid = fork()) == 0)
		{
			tcsetattr(0,TCSADRAIN, &termios1);
			if (ft_get_cmd(pipefd))
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
		tcsetattr(0,TCSADRAIN, &termios2);
		ft_child2(pipefd, env);
	}
	return (0);
}
