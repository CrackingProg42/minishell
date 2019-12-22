/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipe_redirection_comma.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 11:39:38 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/22 21:34:34 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int			ft_check_if_comma(char *str)
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


int			ft_check_if_pipe(char *str)
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

t_redir		init_redir(t_redir redir)
{
	redir.putfile = 0;
	redir.putendfile = 0;
	redir.in = 0;
	redir.path = 0;
	return (redir);
}

t_redir		check_redir_help(int i, char *str, t_redir redir)
{
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
		redir.putendfile = 1;
	else if (str[i] == '<')
		redir.in = 1;
	else if (str[i] == '>' && str[i + 2] != '>')
		redir.putfile = 1;
	return (redir);
}

void		init_check_redir(int *i, int *dquote, int *quote)
{
	*quote = 1;
	*dquote = 1;
	*i = -1;
}

t_redir		ft_check_redirection(char *str)
{
	int			i;
	int			quote;
	int			dquote;
	t_redir		redir;

	init_check_redir(&i, &dquote, &quote);
	redir = init_redir(redir);
	while (str[++i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1: 0;
		if (str[i] == '<' || str[i] == '>')
			if (quote == 1 && dquote == 1)
			{
				redir = check_redir_help(i, str, redir);
				if (str[++i] == '>')
					i++;
				while (str[i] == ' ')
					i++;
				redir.path = ft_dup_to_space(&str[i]);
				return (redir);
			}
	}
	return (redir);
}
