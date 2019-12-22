/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:24:51 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/22 21:34:43 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_print_header(void)
{
	ft_putstrfd(1,"\033[2m>>\033[0m");
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
