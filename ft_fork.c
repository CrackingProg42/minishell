/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 22:03:25 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/26 19:05:10 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_cut_quote(char *str)
{
	int i;

	i = ft_jump_space(str);
	if (str[i] == '\'')
	{
		str[i] = ' ';
		i++;
		while (str[i] != '\'' && str[i])
			i++;
		str[i] = ' ';
	}
	else if (str[i] == '\"')
			{
				str[i] = ' ';
				i++;
				while (str[i] != '\"' && str[i])
					i++;
				str[i] = ' ';
			}
}

void	ft_cut_redirection(char *str, t_redir redir)
{
	int lenght;

	lenght = 0;
	redir.in ? lenght = ft_lenght_to_cara(str, '<') : 0;
	redir.putfile || redir.putendfile? lenght = ft_lenght_to_cara(str, '>') : 0;
	if (lenght > 0)
		str[lenght] = '\0';
}

int     ft_fork(char **str, t_env *env)
{
    int pipefd[2];
	int i;
	int save;
	t_redir redir;
	int status;

	save = 0;
	i = -1;
	while (str[++i])
	{
		if (pipe(pipefd) == -1)
	   		return (1);
		redir = ft_check_redirection(str[i]);
		ft_cut_redirection(str[i], redir);
		if (ft_redirection(redir, pipefd, &save))
			if(ft_invalidcmd(str[i], 1, env))
				continue ;
		if (!ft_concordance(str[i], env))
			continue ;
		if ((g_child = fork()) == 0)
   		{
        	dup2(save, 0);
			if (str[i + 1] != NULL || redir.putfile || redir.putendfile)
				dup2(pipefd[1], 1);
        	close(pipefd[0]);
			ft_printable(str[i], env);
		}		
		waitpid(g_child, &status,0);
		g_dollar = (char)WEXITSTATUS(status);
		g_dollar == 127 ? ft_invalidcmd(str[i], 0, env) : 0;
		close(pipefd[1]);
		save = pipefd[0];
	}
    return (0);
}
