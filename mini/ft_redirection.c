/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:46:12 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/16 20:54:27 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redirection(t_redir redir, int pipefd[2], int save)
{
	int fd;

	if (redir.path == NULL)
		return (0);
	if (redir.putendfile)
	{
		if ((fd = open(redir.path, O_RDWR | O_CREAT | O_APPEND , 0666)) == -1)
			return (-1);
		close(pipefd[1]);
		dup2(fd ,pipefd[1]);
	}		
	if (redir.putfile)
	{
		if ((fd = open(redir.path, O_RDWR | O_TRUNC | O_CREAT , 0666 )) == -1)
			return (-1);
		close(pipefd[1]);
		dup2(fd ,pipefd[1]);
	}
	if (redir.in)
	{
	}
	free(redir.path);	
	if (redir.path && redir.in == 0 && redir.putfile == 0 && redir.putendfile == 0)
		return (1);
	return (0);
}
