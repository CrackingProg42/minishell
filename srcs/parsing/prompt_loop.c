/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:48:38 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/06 22:44:23 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	write(2, LIGHT_BLUE, ft_strlen(LIGHT_BLUE));
	if (!g_open_pipe)
		write(2, PROMPT_START_MSG, ft_strlen(PROMPT_START_MSG));
	else
		write(2, PIPE_START_MSG, ft_strlen(PIPE_START_MSG));
	write(2, NC, ft_strlen(NC));
}

char	*last_token(t_list *token_list)
{
	t_list	*nav;

	nav = token_list;
	while (nav)
	{
		if (!nav->next)
			return (char*)nav->content;
		nav = nav->next;
	}
	return (NULL);
}

char	*prelast_token(t_list *token_list)
{
	t_list	*nav;

	nav = token_list;
	while (nav->next)
	{
		if (!nav->next->next)
			return (char*)nav->content;
		nav = nav->next;
	}
	return (NULL);
}

char	*first_token(t_list *token_list)
{
	t_list	*nav;

	nav = token_list;
	if (nav)
		return (char*)nav->content;
	return (NULL);
}

t_list	*pipe_handle(int depth, t_list **token_list)
{
	t_list	*tmp;

	if (depth == 0)
		g_open_pipe = 1;
	if (!ft_strncmp(first_token((*token_list)), "|", 2)
		&& (ft_lstlen((*token_list)) == 1 || depth > 1))
		g_pipe_error = 1;
	else
	{
		print_prompt();
		tmp = prompt_loop(depth + 1);
		ft_lstadd_back(token_list, tmp);
	}
	if (depth == 0)
		g_open_pipe = 0;
	return ((*token_list));
}

t_list	*prompt_loop(int depth)
{
	char	*line;
	t_list	*token_list;
	int		ret_value;

	g_p_stop_sig = 0;
	if ((ret_value = get_next_line(STDIN_FILENO, &line)) < 0)
	{
		if (ret_value != -2)
			ft_perror(ERR_READLINE);
		exit(0);
		return (NULL);
	}
	token_list = tokenize(line);
	if ((!ft_strncmp(last_token(token_list), "|", 2))
		|| (depth >= 1 && !last_token(token_list)))
	{
		free(line);
		return (pipe_handle(depth, &token_list));
	}
	if (!ft_strncmp(first_token(token_list), "|", 2)
		&& (ft_lstlen(token_list) == 1 || depth > 1))
		g_pipe_error = 1;
	free(line);
	return (token_list);
}
