/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 11:39:38 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/16 22:22:07 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_check_if_comma(char *str)
{
	int i;
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	i = -1;
	while (str[++i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1: 0;
		if (str[i] == ';' && quote == 1 && dquote == 1)
			return (1);
	}
	return (0);
}


int		ft_check_if_pipe(char *str)
{
	int i;
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	i = -1;
	while (str[++i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1: 0;
		if (str[i] == '|' && quote == 1 && dquote == 1)
			return (1);
	}
	return (0);
}

t_redir		ft_check_redirection(char *str)
{
	int i;
	int quote;
	int dquote;
	t_redir redir;

	quote = 1;
	dquote = 1;
	i = -1;
	redir.putfile = 0;
	redir.putendfile = 0;
	redir.in = 0;
	redir.path = 0;
	while (str[++i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1: 0;
		if (str[i] == '<' || str[i] == '>')
			if (quote == 1 && dquote == 1)
			{
				if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
					redir.putendfile = 1;
				else if (str[i] == '<')
					redir.in = 1;
				else if (str[i] == '>' && str[i + 2] != '>')
					redir.putfile = 1;
				i++;
				if (str[i] == '>')
					i++;
				while (str[i] == ' ')
					i++;
				redir.path = ft_dup_to_space(&str[i]);
				return (redir);
			}
	}
	return (redir);
}
