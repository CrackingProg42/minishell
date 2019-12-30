/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 12:51:20 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:19:01 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_continue(char *str)
{
	int i;

	i = ft_strlen(str);
	if (str[i - 1] != '|' && str[i - 1] != '\\')
		return (1);
	return (0);
}

char	*ft_malloc(char *str)
{
	if (!(str = malloc(1)))
		return (0);
	*str = '\0';
	return (str);
}

char	*ft_get_str(char *str, int quote, int dquote, int fd)
{
	char	buf[2];

	if (!(str = ft_malloc(str)))
		return (0);
	while (1)
	{
		if (read(fd, buf, 1) == 0)
		{
			if (*str != '\0')
				continue ;
			return (ft_free_null(str));
		}
		buf[1] = '\0';
		buf[0] == '\'' && dquote == 1 ? quote *= -1 : 0;
		buf[0] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (buf[0] == '\n' && quote == 1 && dquote == 1)
		{
			if (ft_check_continue(str))
				break ;
			continue ;
		}
		if (!(str = ft_save_rest(str, buf)))
			return (0);
	}
	return (str);
}
