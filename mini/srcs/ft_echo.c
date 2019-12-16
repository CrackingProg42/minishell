/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:01:36 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/16 21:11:56 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo_position(char *str)
{
	int i;
	int option;
	
	option = 1;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != ' ' && str[i])
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0' && str[i + 1] != '\0' 
		&& str[i] == '-' && str[i + 1] == 'n')
	{
		i += 2;
		option *= -1; 
	}
	while (str[i] == ' ')
		i++;
	return (i * option);
}


void	ft_print_echo(char *str, char **envp , int i)
{
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	while(str[i])
	{
		if (str[i] == '\'' && dquote == 1) 
		{
			quote *= -1;
			i++;
			continue ;
		}
		if (str[i] == '\"' && quote == 1)
		{
		  	dquote *= -1;
			i++;
			continue ;
		}
		if (str[i] == '$')
		{
		 	 if (!ft_variable(&str[i], &i , envp))
				write(1, &str[i], 1);
		}
		else if ((str[i] != '\"' && str[i] != '\'' && str[i] != '\\' 
		&& str[i] != '$') || (i != 0 && (str[i- 1]) == '\\') 
			|| quote == -1 || dquote == -1)
			write(1, &str[i], 1);
		i++;
	}
}

int		ft_check_quote(char *str)
{
	int quote;
	int dquote;
	int i;

	dquote = 1;
	quote = 1;
	i = -1;
	while (str[++i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1: 0;
	}
	return (dquote == 1 && quote == 1 ? 0 : 1);
}

char 	*ft_get_str(int quote ,int dquote, int fd)
{
	char buf[2];
	char *str;
	int i;

	i = -1;
	if (!(str = malloc(1)))
		return (0);
	*str = '\0';
	while  (1)
	{
		i++;
		if(read(fd, buf, 1) == 0)
		{
			free(str);
			return (NULL);
		}
		buf[1] = '\0';
		if (buf[0] == '\'' && dquote == 1) 
			quote *= -1;
		if (buf[0] == '\"' && quote == 1)
		  	dquote *= -1;
		if (buf[0] == '\n' && quote == 1 && dquote == 1)
		{
			if (str[i - 1] != '|')
				break ;
			else
				continue ;
		}
		if (!(str = ft_save_rest(str, buf)))
			return (0);
	}
	return (str);
}

void	ft_echo(char *str, char **envp)
{
	int option;
	int i;

	i = ft_echo_position(str);
	option = i < 0 ? 1 : 0;
	i = i < 0 ? -i : i;
	ft_print_echo(str, envp, i);
	if (!option)
		write(1, "\n", 1);
}	
