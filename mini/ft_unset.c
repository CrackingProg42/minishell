/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:01:58 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/19 10:49:17 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_cmp_unset(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] && str2[i])
	   i++;
	if (str1[i] == '=')
		return (1);
	return (0);
}
 
void	ft_swap(char **envp)
{
	int i;

	i = 0;
	while(envp[i + 1])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = envp[i + 1];
}

int		ft_unset(char *str, char **envp)
{
	int i;

	str += ft_echo_position(str);
	while (*str == ' ')
		str++;
	i = 0;
	while (envp[i])
	{
		if (ft_cmp_unset(envp[i], str))
		{
			ft_swap(&envp[i]);
			break ;
		}
		i++;
	}
	return (0);
}
	
