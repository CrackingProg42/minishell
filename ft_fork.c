/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:03:25 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/22 21:41:32 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PF r.putfile
#define PEF r.putendfile
#define INV ft_invalidcmd(str[i], 1, *ep))


void	ft_cut(char *str, t_redir redir)
{
	int lenght;

	lenght = 0;
	redir.in ? lenght = ft_lenght_to_cara(str, '<') : 0;
	redir.putfile || redir.putendfile? lenght = ft_lenght_to_cara(str, '>') : 0;
	if (lenght > 0)
		str[lenght] = '\0';
}

void	fork_utils(char a, char ***envp, int *pfd[2], int *s)
{
	dup2(*s, 0);
	close(*pfd[0]);
	ft_printable(a, *envp);
}

int     ft_fork(char **str,char ***ep)
{
	int 		pfd[2];
	int			i;
	int			s;
	t_redir		r;

	s = 0;
	i = -1;
	while (str[++i])
	{
		if (pipe(pfd) == -1)
	   		return (1);
		r = ft_check_redirection(str[i]);
		ft_cut(str[i], r);
		if (((ft_redirection(r, pfd, &s) && INV) || !ft_concordance(str[i], ep))
			continue ;
		if ((g_child = fork()) == 0 && (str[i + 1] != NULL || PF || PEF))
			dup2(pfd[1], 1);
		if (g_child == 0)
			fork_utils(str[i], ep, &pfd, &s);
		waitpid(g_child, &s,0);
		(g_d = (char)WEXITSTATUS(s)) == 127 ? ft_invalidcmd(str[i], 0, *ep) : 0;
		close(pfd[1]);
		s = pfd[0];
	}
    return (0);
}
