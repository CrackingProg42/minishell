/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:40:58 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/17 19:13:27 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(char *str, char **envp)
{
	int ret;

	str += ft_echo_position(str);
	while (*str == ' ')
		str++;
	ret = chdir(str);
	ret == -1 ? ft_cd_error(str, 0, envp) : 0;
	return (0);
}
