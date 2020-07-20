/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:48:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/20 16:10:36 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt()
{
	write(1, LIGHT_BLUE, ft_strlen(LIGHT_BLUE));
	if (!g_open_pipe)
		write(1, PROMPT_START_MSG, ft_strlen(PROMPT_START_MSG));
	else
		write(1, PIPE_START_MSG, ft_strlen(PIPE_START_MSG));
	write(1, NC, ft_strlen(NC));
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

char 	*first_token(t_list *tokenlist)
{
	t_list	*nav;

	nav = tokenlist;
	if (nav)
		return (char*)nav->content;
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
			g_open_pipe = 1;
		if (!ft_strncmp(first_token(tokenList), "|", 2) && (ft_lstlen(tokenList) == 1 || depth > 1))
			g_pipe_error = 1;
		else
		{
			print_prompt();
			tmp = prompt_loop(depth + 1);
			ft_lstadd_back(&tokenList, tmp);
		}
		if (depth == 0)
			g_open_pipe = 0;
		return (tokenList);
	}
	if (!ft_strncmp(first_token(tokenList), "|", 2) && (ft_lstlen(tokenList) == 1 || depth > 1))
		g_pipe_error = 1;
	free(line);
	return (tokenList);
}
