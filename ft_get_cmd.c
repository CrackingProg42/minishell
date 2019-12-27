/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stupid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 22:41:08 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/26 11:53:17 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pipe(char *str)
{
	int i;
	int quote;
	int dquote;
	int a;

	a = 0;
	i = 0;
	quote = 1;
	dquote = 1;
	while(*str)
	{
		*str == '\'' && dquote == 1 ? quote *= -1 : 0;	
		*str == '\"' && quote == 1 ? dquote *= -1: 0;
		if (*str == '|' && quote == 1 && dquote == 1)
			i++;
		str++;
	}
	while (a++ < i)
		ft_putstr("pipe ");
   i > 0 ? write(1, ">", 1) : 0;	
}


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
	if (*buf == 27  || *buf == 28 || *buf == 127)
		return (cmd);
	save = ft_strdup(&cmd.str[cmd.posi]);
	cmd.str[cmd.posi] = '\0';
	cmd.str = ft_join(cmd.str, buf);
	cmd.str = ft_join(cmd.str, save);
	return (cmd);
}				

t_cmd	ft_print_cmd(char *buf, t_cmd cmd)
{	
	cmd = ft_join_posi(cmd , buf);
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
	write(1, " ",1);
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
	write(1, " ",1);
	cmd->gau > 0 ? cmd->gau -= 1: 0;
	ft_cursor_goback(cmd->gau - cmd->dro + 1);
	return (1);
}
int		ft_check_cara(char buf[BUFSIZE + 1], t_cmd *cmd)
{
	int ret;

	ret = 0;
	if (buf[0] == 27 && buf[2] != 51 && buf[1] == 91)
	{	
		if ( buf[2] == 68)	
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
	if (*buf > 31  || *buf == 8 || *buf == 10)
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


int		ft_check_pipe(t_cmd *cmd)
{
	int i;

	i = ft_jump_space(cmd->str);
	if (cmd->str[i] == '|' || cmd->str[i] == '\0')
	{
		ft_invalidcmd(cmd->str ,3 ,NULL);
		*cmd = ft_init_str(*cmd);
		return (1);
	}
	while (cmd->str[i])
	{
		if (cmd->str[i] == '|')
		{
			i++;
			i += ft_jump_space(cmd->str);
				if (cmd->str[i] == '|')
				{
					ft_invalidcmd(cmd->str ,3 ,NULL);
					*cmd = ft_init_str(*cmd);
					return (1);
				}
		}	
		i++;
	}
	return (0);
}

t_cmd	ft_change_line(t_cmd cmd)
{
	cmd.aff = 0;
	cmd.gau = 0;
	cmd.dro = 0;
	cmd.posi = cmd.len;
   	return (cmd);
}	


char 	*ft_cmd_take(int quote ,int dquote)
{
	char buf[BUFSIZE + 1];
	int ret;
	t_cmd cmd;

	cmd.str = NULL;
	cmd = ft_init_str(cmd);
	while  (1)
	{
		if (!cmd.str)
			return (0);
		ret = read(0, buf, BUFSIZE);
		if (*buf == 4)
			return (0);
		buf[ret] = '\0';
		if(ft_check_cara(buf, &cmd))
		{
			if (*buf == 3)
				cmd = ft_init_str(cmd);
			continue;
		}
		buf[0] == '\'' && dquote == 1 ? quote *= -1 : 0;
		buf[0] == '\"' && quote == 1 ? dquote *= -1: 0;
		if (buf[0] == 10 && quote == 1 && dquote == 1)
		{
			if (cmd.str[cmd.len - 1] != '|' && cmd.str[cmd.len - 1] != '\\')
				break ;
			if (ft_check_pipe(&cmd))
				continue ;
		}
		if (buf[0] == 10)
			cmd = ft_change_line(cmd);
		cmd = ft_print_cmd(buf, cmd);
	}
	return (cmd.str);
}

int		ft_get_cmd(int pipe[2])
{
	char *str;

	if (!(str =ft_cmd_take(1, 1)))
		return (1);
	ft_putstrfd(pipe[1], str);
	write(pipe[1], "\n",1);
	write(1, "\n",1);
	return (0);
}
