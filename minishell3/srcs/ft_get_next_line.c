/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:46:05 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/12 17:01:22 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		have_nl(char *str)
{
	int i;

	i = 0;
	while (str[i])
		if (str[i++] == '\n')
			return (1);
	return (0);
}

char	*ft_save_rest(char *str1, char *str2)
{
	int i;
	int a;
	char*dest;

	i = 0;
	a = 0;
	while (str1[i])
		i++;
	while (str2[a])
		a++;
	if (!(dest = malloc(a + i + 1)))
		return (0);
	i = -1;
	while (str1[++i])
		dest[i] = str1[i];
	a = -1;
	while (str2[++a])
		dest[i++] = str2[a];
	dest[i] = '\0';
	free(str1);
	return (dest);
}

int		ft_len2cara(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*get_line(char **line, char *tmp)
{
	int			i;
	static char *save;
	int			a;
	char		*dest;

	i = ft_len2cara(tmp, '\n');
	if (!(dest = malloc(i + 1)))
		return (0);
	a = ft_len2cara(&tmp[i], '\0');
	if (!(save = malloc(a + 2)))
		return (NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		dest[i] = tmp[i];
		i++;
	}
	dest[i++] = '\0';
	a = 0;
	while (tmp[i])
		save[a++] = tmp[i++];
	save[a] = '\0';
	free(tmp);
	*line = dest;
	return (save);
}

char	*ft_malloc(char *save)
{
	if (save == NULL)
	{
		if (!(save = malloc(1)))
			return (NULL);
		*save = '\0';
	}
	return (save);
}

int		get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	int			ret;
	static char	*save;

	if (((ret = 1) == 1) && fd < 0)
		return (-1);
	if (save == NULL && !(save = ft_malloc(save)))
		return (-1);
	if (have_nl(save))
		return (save = get_line(line, save)) > 0 ? 1 : -1;
	while (ret)
	{
		if ((ret = read(fd, buff, BUFFER_SIZE)) < 0)
			return (-1);
		if (*buff == '\0')
			return (-1);
		buff[ret] = '\0';
		if (!(save = ft_save_rest(save, buff)))
			return (-1);
		if (have_nl(save) || ret == 0)
		{
			if (!(save = get_line(line, save)))
				return (-1);
			break ;
		}
	}
	return (ret == 0 ? -1 : 1);
}
