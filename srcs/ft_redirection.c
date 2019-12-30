/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:46:12 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:48:25 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_redir_2(t_redir redir, int pipefd[2], int *save, int fd)
{
	if (redir.path == NULL)
		return (0);
	if (redir.putendfile)
	{
		if ((fd = open(redir.path, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
			return (ft_error_redir(redir.path, 2));
		close(pipefd[1]);
		dup2(fd, pipefd[1]);
	}
	if (redir.putfile)
	{
		if ((fd = open(redir.path, O_RDWR | O_TRUNC | O_CREAT, 0666)) == -1)
			return (ft_error_redir(redir.path, 2));
		close(pipefd[1]);
		dup2(fd, pipefd[1]);
	}
	if (redir.in)
	{
		if ((fd = open(redir.path, O_RDONLY)) == -1)
			return (ft_error_redir(redir.path, 1));
		*save = fd;
	}
	if (redir.path && !redir.in && !redir.putfile && !redir.putendfile)
		return (ft_error_redir(redir.path, 0));
	return (!ft_free(redir.path));
}
