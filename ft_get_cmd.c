/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stupid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 22:41:08 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/20 10:04:31 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmd_take(int quote ,int dquote, int fd)
{
	char buf[2];
	char save;
	
	buf[0] = '\0';
	while  (1)
	{
		save = buf[0];
		if(read(0, buf, 1) == 0)
		{
			if (save != '\0')
				continue ;
			return (1);
		}
		buf[1] = '\0';
		if (buf[0] == '\'' && dquote == 1)
			quote *= -1;
		if (buf[0] == '\"' && quote == 1)
		  	dquote *= -1;
		if (buf[0] == '\n' && quote == 1 && dquote == 1)
		{
			if (save != '|' && save != '\\')
				break ;
			else
				continue ;
		}
		write(fd, buf , 1);
	}
	return (0);
}

int		ft_get_cmd(int pipe)
{
	ft_home();
	if (ft_cmd_take(1, 1 ,pipe))
		return (1);
	write(pipe, "\n",1);
	return (0);
}
