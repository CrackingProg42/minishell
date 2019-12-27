/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:54:44 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/27 10:20:28 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_export(char *str, int lenght)
{
	int quote;
	int dquote;
	int i;

	dquote = 1;
	quote = 1;
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '_' && str[i + 1] == '=')
		return (1);
	while (lenght-- && str[i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1: 0;
		if (str[i] == '='  && quote == 1 && dquote == 1)
		{
			if (i == 0 || str[i + 1] == ' ' || str[i + 1] == '\0')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int		ft_cmp_export(char *str1, char *str2)
{
	int i;

	i = 0;
	while(str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return ((str1[i] == '=' && str2[i] == '\0') ? 1 : 0);
}

char *ft_local(char *str, char **local)
{
	int i;

	i = 0;
	while (local[i])
	{
		if (ft_cmp_export(local[i], str))
				return (ft_strdup(local[i]));
		i++;
	}
	return (0);
}

char 	*ft_dup_export(char *str, char **local)
{
	char *dest;
	int i;
	int lenght;
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	lenght = ft_lenght_to_cara(str, ' ');
	if ((dest = ft_local(str,local)))
		return (dest);
	if (ft_check_export(str, lenght))
			return (0);
	if (!(dest = malloc(lenght + 1)))
		return (0);
	i = 0;
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


char 	*ft_get_var(char *str,char **local)
{
	int i;
	char *new_v;

	str += ft_echo_position(str);
	i = ft_lenght_to_cara(str, '=');
	while (str[i] != ' ')
		i--;
	i++;
	if (!(new_v = ft_dup_export(&str[i], local)))
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

char **ft_new_envp(char **envp, char *new)
{
	char **new_env;
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

int	ft_export(char *str, t_env *env)
{
	char *new_v;
	int i;

	i = ft_echo_position(str);
	i += ft_jump_space(&str[i]);
	if (str[i] == '\0')
	{
		g_dollar = 0;
		return (ft_invalidcmd(str, 4,env));
	}
	g_dollar = 127;
	if (!(new_v = ft_get_var(str, env->local)))
		return (1);
	if (!(env->envp = ft_new_envp(env->envp, new_v)))
		return (0);
	g_dollar = 0;
	return (1);
}
