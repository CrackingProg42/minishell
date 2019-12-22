/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 13:23:00 by QFM               #+#    #+#             */
/*   Updated: 2019/12/21 15:23:35 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_pipes(int pipes)
{
	while (pipes--)
	{
		write(1, "pipe", 4);
		if (pipes != 0)
			write(1, " ", 1);
	}
	write(1, "> ", 2);
}

char 	*ft_get_input(int quote ,int dquote, int fd)
{
	char 	buf[2];
	char	*str;
	int		i;
	int		count_pipe;

	count_pipe = 0;
	i = 0;
	if (!(str = malloc(1)))
		return (0);
	*str = '\0';
	while  (1)
	{
		if(read(fd, buf, 1) == 0)
		{
			if (*str != '\0')
				continue ;
			free(str);
			return (NULL);
		}
		buf[1] = '\0';
		if (buf[0] == '\'' && dquote == 1) 
			quote *= -1;
		if (buf[0] == '\"' && quote == 1)
		  	dquote *= -1;
		if (buf[0] == '\n' && quote == 1 && dquote == 1)
		{
			if (i != 0 && str[i - 1] != '|' && str[i - 1] != '\\')
				break ;
			else
			{
				if ((fd == 0 && str[i - 1] == '\\') || (fd == 0 && str[i - 1] == '|'))
				{
					if (str[i - 1] == '|')
					{
						count_pipe++;
						if (i == 1 || str[i - 2] == '|')
						{
							ft_invalidcmd(str, 3, NULL);
							
						}
					}
					ft_print_pipes(count_pipe);
				}
				continue ;
			}
		}
		if (!(str = ft_save_rest(str, buf)))
			return (0);
		i++;
	}
	return (str);
}