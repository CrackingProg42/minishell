/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:58:55 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/26 20:00:17 by paszhang         ###   ########.fr       */
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

int		ft_cmp2(char *str1, char *str2)
{
	int i;

	i = 0;
	while(str1[i] == ' ')
		i++;
	while(str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return (str2[i] == '\0' && str1[i] == '=') ? 1 : 0;
}

int		ft_variable(char *str, int *a, t_env *env, int *quote, int *dquote)
{
	int i;
	
	i = -1;
	str++;
	while (str[++i])
	{		
		str[i] == '\'' && *dquote == 1 ? *quote = *quote * -1 : 0;
		str[i] == '\"' && *quote == 1 ? *dquote = *dquote * -1: 0;
		if (*quote == 1 && *dquote == 1 && (str[i] == '\"' || str[i] == '\'' || str[i] == ' '))
				break ;
	}
	*a = *a + i + 1;
	str[i] = '\0';
	*str == '\"' || *str == '\"' ? str++ : 0;
	i = 0;
	while (env->envp[i])
	{
		if (ft_cmp2(env->envp[i], str))
		{
			ft_write_variable(env->envp[i]);			
			return (1);
		}
		i++;
	}
	i = 0;
	while (env->local[i])
	{
		if (ft_cmp2(env->local[i], str))
		{
			ft_write_variable(env->local[i]);			
			return (1);
		}
		i++;
	}
	return (0);
}

