/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:24:51 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/15 12:09:03 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_print_header(void)
{
	ft_putstrfd(1,"\033[37m¯\\\033[31m_\033[1;34m(ツ)\033[31m_\033[37m/¯\033[2m>>\033[0m");
}

void	ft_home(void)
{
	char *str;

	str = getcwd(NULL,0);
	ft_putstrfd(1,"\033[32m");
	ft_putstrfd(1, str);
	free(str);
	ft_print_header();
}
