/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_comma.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:39:15 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/27 10:20:08 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int		ft_cmd(char *str, char **src)
{
	int i;
	char *tmp;
	int lenght;

	lenght = ft_lenght_to_cara(str, ';');
	if (!(tmp = malloc(lenght + 1)))
		return (-1);
	i = 0;
	while (i < lenght)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	str[i] == ';' ? i++ : 0;
	*src = tmp;
	free(str);
	return (i);
}
char **ft_split_egal(char *str)
{
	char **dest;
	int i;

	if (!(dest = malloc(sizeof(char *) * 3)))
		return (0);
	if (!(dest[0] = ft_dup_to_space(str)))
		return (0);
	i = ft_lenght_to_cara(str, ' ');
	dest[1] = NULL;
	if (i != 0)
		if (!(dest[1] = ft_dup_to_space(&str[i +1])))
			return (0);
	printf("i = %d\n",i);
	printf("str 1 = %s\n",dest[0]);
	printf("str 2 = %s\n",dest[1]);
	dest[2] = 0;
	return (dest);
}

char **ft_egal(char *str)
{
	int i;
	int quote;
	int dquote;


	quote = 1;
	dquote = 1;
	i = 0;
	while (str[i] != ' ' && str[i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1: 0;
		if (str[i] == '=' && quote == 1 && dquote == 1)
			return (ft_split_egal(str));
		i++;
	}
	return (ft_split(str, '\0'));
}

void	ft_local_add(char *str, t_env *env)
{
	env->local = ft_new_envp(env->local, str);
}	

char	*ft_cut_egal(char *str, t_env *env)
{
	char **src;

	if (!(src = ft_egal(str)))
		return (0);
	if (src[1] != NULL)
	{
		ft_local_add(src[0] ,env);
		free(src);
		return (src[1]);
	}
	free(src);
	return (src[0]);
}

int		ft_cut_comma(char *str, t_env *env)
{
	char *src;
	int ret;

	
	if (*str == '\0')
		return (0);
	if (!(str = ft_cut_egal(str, env)))
		return (1);
	if (*str == '\0')
	{
		free(str);
		return (0);
	}
	while (*str)
	{
		if ((ret = ft_cmd(str, &src)) == -1)
			return (1);
		str += ret;
		if (!(src = ft_strtrim(src, " ")))
			return (1);
		if (ft_cut_pipe(src, env))
			return (ft_free(src));
		while (*str && *str == ' ')
			str++;
	}
	return (0);
}

