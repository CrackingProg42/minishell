/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:58:55 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 18:42:28 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmp2(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return ((str2[i] == '\0' || str2[i] == ' ') && str1[i] == '=') ? 1 : 0;
}

char	*ft_find_variable(char *str, t_env *env)
{
	int i;
	int lenght;

	i = -1;
	while (env->envp[++i])
		if (ft_cmp2(env->envp[i], str))
		{
			lenght = ft_lenght_to_cara(env->envp[i], '=');
			return (&env->envp[i][lenght + 1]);
		}
	i = -1;
	while (env->local[++i])
	{
		if (ft_cmp2(env->local[i], str))
		{
			lenght = ft_lenght_to_cara(env->local[i], '=');
			return (&env->local[i][lenght + 1]);
		}
	}
	return (ft_strdup(""));
}

char	*ft_variable(char *str, int i, t_env *env)
{
	char*var;
	int a;
	char*save;

	if (str[i + 1] == '?')
		var = ft_itoa((int)g_dollar);
	else
		var = ft_find_variable(&str[i + 1], env);
	a = ft_lenght_to_cara(&str[i], ' ') + i;
	str[i] = '\0';
	save = var;
	var = ft_join(str, var);
	if (*save == '\0' || str[i + 1] == '?')
		free(save);
	save = var;
	var = ft_join(var, &str[a]);
	free(save);
	free(str);
	return (var);
}

char	*ft_check_variable(char *str, t_env *env)
{
	int i;
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	i = -1;
	while (str[++i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (str[i] == '$' && quote == 1 && dquote == 1)
		{
			if (!(str = ft_variable(str, i, env)))
				return (0);
			i = -1;
		}
	}
	return (str);
}
