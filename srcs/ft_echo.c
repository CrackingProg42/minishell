/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:01:36 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/22 21:34:46 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (str[i] == '\'' && dquote == 1 && i++ > -1 && (quote *= -1))
			continue ;
		if (str[i] == '\"' && quote == 1 && i++ > -1)
		{
		  	dquote *= -1;
			continue ;
		}
		if (str[i] == '$' && !ft_variable(&str[i], &i , envp, &quote , &dquote))
			write(1, &str[i], 1);
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

int		get_str_utils(int *quote, int *dquote, char buf)
{
	if (buf == '\'' && *dquote == 1)
		*quote *= -1;
	if (buf == '\"' && *quote == 1)
		*dquote *= -1;
}

char 	*ft_get_str(int q ,int dq, int fd)
{
	char b[2];
	char *s;
	int i;
	int ret;

	i = 0;
	if (!((s = (char *)malloc(1)) && (*s = '\0')=='\0'))
		return (0);
	while (1)
	{
		if((b[1] = '\0') != '1' && (ret = read(fd, b, 1)) == 0 && *s != '\0')
			continue ;
		if(ret == 0)
			return (ft_free_null(&s));
		get_str_utils(&q, &dq, b[0]);
		if (b[0] == '\n' && q == 1 && dq == 1 && i != 0 && \
			s[i - 1] != '|' && s[i - 1] != '\\')
			break ;
		if (b[0] == '\n' && q == 1 && dq == 1)
			continue ;
		if (!(s = ft_save_rest(s, b)))
			return (0);
		i++;
	}
	return (s);
}

int	ft_echo(char *str, char **envp)
{
	int option;
	int i;

	i = ft_echo_position(str);
	option = i < 0 ? 1 : 0;
	i = i < 0 ? -i : i;
	ft_print_echo(str, envp, i);
	if (!option)
		write(1, "\n", 1);
	return (0);
}	
