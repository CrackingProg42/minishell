/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:54:44 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 18:44:38 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dup_export(char *str, int lenght, int i)
{
	char*dest;
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	if (!(dest = malloc(lenght + 1)))
		return (0);
	while (i < lenght && *str)
	{
		if (*str == '\'' && dquote == 1)
		{
			quote *= -1;
			str++;
		}
		if (*str == '\"' && quote == 1)
		{
			str++;
			dquote *= -1;
		}
		dest[i++] = *str++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_get_var(char *str, char **local)
{
	int i;
	char*new_v;
	char*dest;
	int lenght;

	str += ft_echo_position(str);
	i = ft_lenght_to_cara(str, '=');
	while (str[i] != ' ')
		i--;
	i++;
	lenght = ft_lenght_to_cara(&str[i], ' ');
	if ((dest = ft_local(&str[i], local)))
		return (dest);
	if (ft_check_export(&str[i], lenght))
		return (0);
	if (!(new_v = ft_dup_export(&str[i], lenght, 0)))
		return (0);
	return (new_v);
}

int		ft_cmp_envp(char **envp, char *new)
{
	int i;

	i = -1;
	while (envp[++i])
		if (ft_cmp_to_cara(envp[i], new, '='))
		{
			free(envp[i]);
			envp[i] = new;
			return (1);
		}
	return (0);
}

char	**ft_new_envp(char **envp, char *new)
{
	char**new_env;
	int i;

	if (ft_cmp_envp(envp, new))
		return (envp);
	i = 0;
	while (envp[i])
		i++;
	if (!(new_env = malloc(sizeof(char *) * (i + 3))))
		return (0);
	i = -1;
	while (envp[++i])
		new_env[i] = envp[i];
	new_env[i++] = new;
	new_env[i] = NULL;
	free(envp);
	return (new_env);
}

int		ft_export(char *str, t_env *env)
{
	char*new_v;
	int i;

	i = ft_echo_position(str);
	i += ft_jump_space(&str[i]);
	if (str[i] == '\0')
		return (ft_invalidcmd(str, 4, env));
	g_dollar = 127;
	if (!(new_v = ft_get_var(str, env->local)))
		return (1);
	if (!(env->envp = ft_new_envp(env->envp, new_v)))
		return (0);
	g_dollar = 0;
	return (1);
}
