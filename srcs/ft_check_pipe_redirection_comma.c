/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 11:39:38 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:47:52 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir		ft_redir(char *str, int i, t_redir redir)
{
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] != '>')
		redir.putendfile = 1;
	else if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
		redir.in = 1;
	else if (str[i] == '>' && str[i + 2] != '>')
		redir.putfile = 1;
	i++;
	if (str[i] == '>')
		i++;
	i += ft_jump_space(&str[i]);
	redir.path = ft_dup_to_space(&str[i]);
	redir.path = ft_redi_quote(redir.path);
	return (redir);
}

t_redir		ft_check_redirection(char *str)
{
	int		i;
	int		quote;
	int		dquote;
	t_redir	redir;

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
		str[i] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (str[i] == '<' || str[i] == '>')
			if (quote == 1 && dquote == 1)
				return (ft_redir(str, i, redir));
	}
	return (redir);
}
