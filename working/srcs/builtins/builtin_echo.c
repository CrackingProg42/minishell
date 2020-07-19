/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:44:06 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/17 18:03:47 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_echo(char **argv)
{
	int		i;
	char	option_n;
	
	i = 1;
	option_n = 0;
	if (!ft_strncmp(argv[1], "-n", 3))
	{
		option_n = 1;
		i++;
	}
	if (argv[i])
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	while (argv[i])
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	}
	if (!option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
