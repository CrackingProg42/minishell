/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 16:08:22 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 16:56:48 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cursor_goback(int i)
{
	char ret[4];

	ret[0] = 27;
	ret[1] = 91;
	ret[2] = 68;
	ret[3] = 0;
	while (i-- > 0)
		ft_putstr(ret);
}

t_cmd	ft_join_posi(t_cmd cmd, char *buf)
{
	char *save;

	if (*buf == 27 || *buf == 28 || *buf == 127)
		return (cmd);
	save = ft_strdup(&cmd.str[cmd.posi]);
	cmd.str[cmd.posi] = '\0';
	cmd.str = ft_join(cmd.str, buf);
	cmd.str = ft_join(cmd.str, save);
	return (cmd);
}

t_cmd	ft_print_cmd(int ret, char *buf, t_cmd cmd)
{
	cmd = buf[0] == 10 ? ft_change_line(cmd) : cmd;
	buf[ret] = '\0';
	cmd = ft_join_posi(cmd, buf);
	ft_cursor_goback(cmd.affpo);
	ft_putstr(&cmd.str[cmd.len - cmd.aff]);
	if (*buf != 27 && *buf != 28 && *buf != 127)
	{
		cmd.len += 1;
		*buf != 10 ? cmd.aff += 1 : 0;
		*buf == 10 ? print_pipe(cmd.str) : 0;
	}
	cmd.posi = cmd.len - cmd.gau + cmd.dro;
	cmd.affpo = cmd.aff - cmd.gau + cmd.dro;
	ft_cursor_goback(cmd.gau - cmd.dro);
	return (cmd);
}

int		ft_delete_127(t_cmd *cmd)
{
	char *save;

	if (cmd->affpo == 0)
		return (1);
	ft_cursor_goback(cmd->affpo);
	cmd->str[cmd->posi - 1] = '\0';
	save = ft_strdup(&cmd->str[cmd->posi]);
	cmd->str = ft_join(cmd->str, save);
	ft_putstr(&cmd->str[cmd->len - cmd->aff]);
	cmd->len -= 1;
	cmd->aff -= 1;
	cmd->posi = cmd->len - cmd->gau + cmd->dro;
	cmd->affpo = cmd->aff - cmd->gau + cmd->dro;
	write(1, " ", 1);
	ft_cursor_goback(cmd->gau - cmd->dro + 1);
	return (1);
}

int		ft_delete(t_cmd *cmd)
{
	char *save;

	if (cmd->aff == 0 || cmd->posi == cmd->len)
		return (1);
	ft_cursor_goback(cmd->affpo);
	cmd->str[cmd->posi] = '\0';
	save = ft_strdup(&cmd->str[cmd->posi + 1]);
	cmd->str = ft_join(cmd->str, save);
	ft_putstr(&cmd->str[cmd->len - cmd->aff]);
	cmd->len = cmd->len - 1;
	cmd->aff = cmd->aff - 1;
	write(1, " ", 1);
	cmd->gau > 0 ? cmd->gau -= 1 : 0;
	ft_cursor_goback(cmd->gau - cmd->dro + 1);
	return (1);
}
