/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:24:51 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:26:21 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_to_space(char *str)
{
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	while (*str)
	{
		if (*str == ' ' && quote == 1 && dquote == 1)
			break ;
		if (*str == '\'' && dquote == 1)
		{
			quote *= -1;
			str++;
			continue ;
		}
		if (*str == '\"' && quote == 1)
		{
			dquote *= -1;
			str++;
			continue ;
		}
		write(1, str++, 1);
	}
}

void	print_pipe(char *str)
{
	int i;
	int quote;
	int dquote;
	int a;

	a = 0;
	i = 0;
	quote = 1;
	dquote = 1;
	while (*str)
	{
		*str == '\'' && dquote == 1 ? quote *= -1 : 0;
		*str == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (*str == '|' && quote == 1 && dquote == 1)
			i++;
		str++;
	}
	while (a++ < i)
		ft_putstr("pipe ");
	i > 0 ? write(1, ">", 1) : 0;
}

void	ft_print_2d(char **str)
{
	while (*str)
	{
		ft_putstr(*str++);
		ft_putstr("\n");
	}
}

void	ft_print_header(void)
{
	ft_putstrfd(1, "\033[37m¯\\\033[31m_\033[1;34m\
(ツ)\033[31m_\033[37m/¯\033[2m>>\033[0m");
}

void	ft_home(void)
{
	char *str;

	str = getcwd(NULL, 0);
	ft_putstrfd(1, "\033[32m");
	ft_putstrfd(1, str);
	free(str);
	ft_print_header();
}
