/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:03:25 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/17 11:17:32 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cut(char *str, t_redir redir)
{
	int lenght;

	lenght = 0;
	redir.in ? lenght = ft_lenght_to_cara(str, '<') : 0;
	redir.putfile || redir.putendfile? lenght = ft_lenght_to_cara(str, '>') : 0;
	if (lenght > 0)
		str[lenght] = '\0';
}

int     ft_fork(char **str,char ***envp)
{
    int pipefd[2];
	int i;
	int save;
	t_redir redir;
	
	save = 0;
	i = -1;
	while (str[++i])
	{
		if (pipe(pipefd) == -1)
	   		return (1);
		redir = ft_check_redirection(str[i]);
		ft_cut(str[i], redir);
		if (ft_redirection(redir, pipefd, &save))
			if(ft_invalidcmd(str[i], 1, *envp))
				continue ;
		if (ft_concordance(str[i], envp, 0))
			continue ;
		if ((g_child = fork()) == 0)
   		{
        	dup2(save, 0);
			if (str[i + 1] != NULL || redir.path)
				dup2(pipefd[1], 1);
        	close(pipefd[0]);
			ft_concordance(str[i], envp, 1);
			exit(0);
		}
		wait(NULL);
		close(pipefd[1]);
		save = pipefd[0];
	}
    return (0);
}
