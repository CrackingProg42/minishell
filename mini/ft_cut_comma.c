/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_comma.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:39:15 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/16 20:34:18 by paszhang         ###   ########.fr       */
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
	return (i);
}

int		ft_cut_comma(char *str, char **envp)
{
	char *src;
	int ret;

	while (*str)
	{
		if ((ret = ft_cmd(str, &src)) == -1)
			return (1);
		str += ret;
		if (!(src = ft_strtrim(src, " ")))
			return (1);
		if (ft_cut_pipe(src, envp))
			return (ft_free(src));
		while (*str && *str == ' ')
			str++;
	}
	return (0);
}

