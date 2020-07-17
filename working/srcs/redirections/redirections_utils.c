/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:28:06 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/07/17 15:49:15 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				len_to_space(char *str) {
	int		i;

	i = 0;
	while (*str && *str++ != ' ')
		i++;
	return (i);
}

char			*get_word(char *str) {
	int 	i;
	char	*new;

	i = len_to_space(str);
	new = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i] != ' ')
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

t_redirection	stock_redir(char *cmd) {
	int				i;
	t_quotes		quote;
	t_redirection	redir;

	quote.q = -1;
	quote.dq = -1;
	i = -1;
	redir.putfile = 0;
	redir.putendfile = 0;
	redir.in = 0;
	redir.file = 0;
	while (cmd[++i]) {
		cmd[i] == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
		cmd[i] == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
		if ((cmd[i] == '<' || cmd[i] == '>') && quote.q == -1 && quote.dq == -1) {
			if (cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] != '>')
				redir.putendfile = 1;
			else if (cmd[i] == '>' && cmd[i + 2] != '>')
				redir.putfile = 1;
			else if (cmd[i] == '<')
				redir.in = 1;
			i++;
			if (cmd[i] == '>')
				i++;
			while (cmd[i] == ' ')
				i++;
			redir.file = get_word(&cmd[i]);
			return (redir);
		}
	}
	return (redir);
}

int		redirection(t_redirection redir, int (*pipefd)[2], int *save) {
	int		fd;

	if (redir.file == NULL)
		return (0);
	if (redir.in) {
		if ((fd = open(redir.file, O_RDONLY)) == -1)
			return (-1);
		*save = fd;
	}
	if (redir.putendfile) {
		if ((fd = open(redir.file, O_RDWR | O_CREAT | O_APPEND , 0666)) == -1)
			return (-1);
		close((*pipefd)[1]);
		(*pipefd)[1] = fd;
	}
	if (redir.putfile) {
		if ((fd = open(redir.file, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
			return (-1);
		close((*pipefd)[1]);
		(*pipefd)[1] = fd;
	}
	free(redir.file);
	if (redir.file && redir.in == 0 && redir.putfile == 0 && redir.putendfile == 0)
		return (1);
	return (0);
}

void cmd_to_rafter(char ***cmd) {
	int 	i;

	i = 0;
	while ((*cmd)[i])
    {
		if (!ft_strncmp((*cmd)[i], ">", 1) 
			|| !ft_strncmp((*cmd)[i], "<", 2)) 
        {
			(*cmd)[i] = NULL;
			break ;
		}
		i++;
	}
}

char			*table_to_string(char **table) {
    char    *str;
    int     i;

    i = 0;
    str = malloc(1);
    while (table[i])
        str = ft_strjoin_free(str, table[i++]);
    return str;
} 