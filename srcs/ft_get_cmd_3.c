/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 16:10:53 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 17:02:25 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_cara_2(char buf[4], t_cmd *cmd)
{
	if (buf[2] == 68)
		(cmd->aff - cmd->gau + cmd->dro) > 0 ? cmd->gau = cmd->gau + 1 : 0;
	if (buf[2] == 70)
	{
		cmd->dro = 0;
		cmd->gau = 0;
	}
	if (buf[2] == 72)
	{
		cmd->dro = 0;
		cmd->gau = cmd->len;
	}
	if (buf[2] == 67)
		cmd->gau > cmd->dro ? cmd->dro = cmd->dro + 1 : 0;
}

int		ft_check_cara(char buf[4], t_cmd *cmd)
{
	if (buf[0] == 27 && buf[2] != 51 && buf[1] == 91)
	{
		ft_check_cara_2(buf, cmd);
		return (0);
	}
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51)
		return (ft_delete(cmd));
	if (buf[0] == 127)
		return (ft_delete_127(cmd));
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		return (1);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		return (1);
	if (*buf > 31 || *buf == 8 || *buf == 10)
		return (0);
	return (1);
}

t_cmd	ft_init_str(t_cmd cmd)
{
	cmd.posi = 0;
	cmd.len = 0;
	cmd.gau = 0;
	cmd.dro = 0;
	cmd.aff = 0;
	cmd.affpo = 0;
	if (cmd.str != NULL)
	{
		write(1, "\n", 1);
		free(cmd.str);
	}
	if (!(cmd.str = malloc(1)))
		return (cmd);
	*cmd.str = '\0';
	ft_home();
	return (cmd);
}

t_cmd	ft_change_line(t_cmd cmd)
{
	cmd.aff = 0;
	cmd.gau = 0;
	cmd.dro = 0;
	cmd.posi = cmd.len;
	return (cmd);
}
