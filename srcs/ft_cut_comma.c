/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_comma.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:39:15 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 12:36:11 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmd(char *str, char **src)
{
	int i;
	char*tmp;
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
	return (i);
}

int		ft_cut_comma(char *str, t_env *env)
{
	char*src;
	int ret;
	int i;

	i = 0;
	if (*str == '\0')
		return (0);
	if (!(str = ft_cut_egal(str, env)))
		return (1);
	if (*str != '\0')
		while (str[i])
		{
			if ((ret = ft_cmd(&str[i], &src)) == -1)
				return (1);
			i += ret;
			if (!(src = ft_strtrim(src, " ")))
				return (1);
			if (ft_cut_pipe(src, env))
				return (ft_free(src));
			while (str[i] && str[i] == ' ')
				i++;
		}
	free(str);
	return (0);
}
