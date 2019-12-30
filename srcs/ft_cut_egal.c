/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_egal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 12:27:32 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 12:39:39 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_egal(char *str)
{
	char**dest;
	int i;

	if (!(dest = malloc(sizeof(char *) * 2)))
		return (0);
	if (!(dest[0] = ft_dup_to_space(str)))
		return (0);
	i = ft_lenght_to_cara(str, ' ');
	i += ft_jump_space(&str[i]);
	if (!(dest[1] = ft_strdup(&str[i])))
		return (0);
	return (dest);
}

char	**ft_remove(char *str)
{
	char **dest;

	dest = ft_split(str + 1, '\0');
	return (dest);
}

char	**ft_egal(char *str, int *ret)
{
	int i;
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	str += ft_jump_space(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == ' ')
			break ;
		if (str[i] == '=')
		{
			*ret = 1;
			if (str[i + 1] == ' ' || str[i + 1] == '\0')
				return (ft_split(str, '\0'));
			if (i == 0)
				return (ft_remove(str));
			*ret = 0;
			return (ft_split_egal(str));
		}
	}
	*ret = 1;
	return (ft_split(str, '\0'));
}

void	ft_local_add(char *str, t_env *env)
{
	env->local = ft_new_envp(env->local, str);
}

char	*ft_cut_egal(char *str, t_env *env)
{
	char**src;
	char*save;
	int ret;

	if (!(src = ft_egal(str, &ret)))
		return (0);
	if (ret == 0)
	{
		ft_local_add(src[0], env);
		save = src[1];
		free(src);
		return (save);
	}
	save = src[0];
	free(src);
	return (save);
}
