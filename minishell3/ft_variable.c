/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:58:55 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/11 19:44:23 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_write_variable(char *str)
{
	while(*str != '=')
		str++;
	str++;
	while(*str)
		write(1,str++,1);
}

void	ft_variable(char *str, int *a, char **envp)
{
	int i;

	str++;
	*a = *a + 1;
	i = 0;
	while (envp[i])
	{
		if (ft_cmp_tospace(envp[i], str))
		{
			ft_write_variable(envp[i]);			
			break;
		}
		i++;
	}
	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	*a = *a + i;
}

