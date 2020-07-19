/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:48:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/19 18:15:41 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt()
{
	write(1, LIGHT_BLUE, ft_strlen(LIGHT_BLUE));
	if (!open_pipe)
		write(1, PROMPT_START_MSG, ft_strlen(PROMPT_START_MSG));
	else
		write(1, PIPE_START_MSG, ft_strlen(PIPE_START_MSG));
	write(1, NC, ft_strlen(NC));
}

int		token_len(t_list *tokens)
{
	int 	i;

	i = 0;
	while (tokens->next)
	{
		tokens = tokens->next;
		i++;
	}
	return i;
}

char 	*last_token(t_list *tokenlist)
{
	t_list	*nav;

	nav = tokenlist;
	while (nav)
	{
		if (!nav->next)
			return (char*)nav->content;
		nav = nav->next;
	}
	return (NULL);
}

t_list *prompt_loop(int depth)
{
	char 	*line;
	t_list	*tmp;
	t_list 	*tokenList;
	int		ret_value;

	g_p_stop_sig = 0;
	if ((ret_value = get_next_line(STDIN_FILENO, &line)) < 0)
	{
		if (ret_value != -2)
			ft_perror(ERR_READLINE);
		exit(0);
		return (NULL);
	}
	tokenList = tokenize(line);
	if ((!ft_strncmp(last_token(tokenList), "|", 2)) || (depth >= 1 && !last_token(tokenList))) {
		if (depth == 0)
			open_pipe = 1;
		if (!ft_strncmp(last_token(tokenList), "|", 2) && ft_lstlen(tokenList) == 1)
			pipe_error = 1;
		else
		{
			print_prompt();
			tmp = prompt_loop(depth + 1);
			ft_lstadd_back(&tokenList, tmp);
		}
		if (depth == 0)
			open_pipe = 0;
		return (tokenList);
	}
	free(line);
	return (tokenList);
}
