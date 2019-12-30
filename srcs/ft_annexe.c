/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_annexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:48:37 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 11:59:33 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lenght_to_cara(char *str, char cara)
{
	int quote;
	int dquote;
	int i;

	dquote = 1;
	quote = 1;
	i = 0;
	while (str[i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (str[i] == cara && quote == 1 && dquote == 1)
			break ;
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int i;
	char*dest;

	i = 0;
	while (s1[i])
		i++;
	if (!(dest = malloc(sizeof(*s1) * (i + 1))))
		return (0);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_dup_to_space(char *str)
{
	char*dest;
	int i;
	int lenght;

	lenght = ft_lenght_to_cara(str, ' ');
	if (!(dest = malloc(lenght + 1)))
		return (0);
	i = 0;
	while (i < lenght)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_close_pipe(int pipefd[2])
{
	close(pipefd[1]);
	close(pipefd[0]);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}
