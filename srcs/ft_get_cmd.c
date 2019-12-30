/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stupid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 22:41:08 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 16:58:42 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_pipe(t_cmd *cmd)
{
	int i;

	i = ft_jump_space(cmd->str);
	if (cmd->str[i] == '|' || cmd->str[i] == '\0')
	{
		ft_invalidcmd(cmd->str, 3, NULL);
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
				ft_invalidcmd(cmd->str, 3, NULL);
				*cmd = ft_init_str(*cmd);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

char	*ft_remove_slash2(char *str, int i)
{
	char *var;
	char *save;

	str[i] = '\0';
	var = ft_strdup(str);
	save = var;
	var = ft_join(var, &str[i + 2]);
	free(save);
	free(str);
	return (var);
}

char	*ft_remove_slash(char *str, int i)
{
	int quote;
	int dquote;

	quote = 1;
	dquote = 1;
	while (str[++i])
	{
		str[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
		str[i] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (str[i] == '\\' && quote == 1 && dquote == 1)
		{
			if (str[i + 1] == ' ')
			{
				write(1, "\n", 1);
				ft_invalidcmd(str, 5, NULL);
				free(str);
				return (ft_strdup(""));
			}
			if (!(str = ft_remove_slash2(str, i)))
				return (0);
			i = -1;
		}
	}
	return (str);
}

char	*ft_cmd_take(t_cmd cmd, char buf[4], int quote, int dquote)
{
	while (1)
	{
		if (!cmd.str)
			return (0);
		cmd.ret = read(0, buf, 4);
		if (*buf == 4)
			return (0);
		if (ft_check_cara(buf, &cmd))
		{
			cmd = *buf == 3 ? ft_init_str(cmd) : cmd;
			continue;
		}
		buf[0] == '\'' && dquote == 1 ? quote *= -1 : 0;
		buf[0] == '\"' && quote == 1 ? dquote *= -1 : 0;
		if (buf[0] == 10 && quote == 1 && dquote == 1)
		{
			if (cmd.str[cmd.len - 1] != '|' && cmd.str[cmd.len - 1] != '\\')
				break ;
			if (ft_check_pipe(&cmd))
				continue ;
		}
		cmd = ft_print_cmd(cmd.ret, buf, cmd);
	}
	return (cmd.str);
}

int		ft_get_cmd(int pipe[2])
{
	char			*str;
	struct termios	termios1;
	struct termios	termios2;
	char			buf[4];
	t_cmd			cmd;

	cmd.str = NULL;
	cmd = ft_init_str(cmd);
	tcgetattr(0, &termios1);
	tcgetattr(0, &termios2);
	termios1.c_cc[VMIN] = 1;
	termios1.c_lflag &= ~(ICANON | ECHO | ISIG | ECHOCTL);
	tcsetattr(0, TCSANOW, &termios1);
	if (!(str = ft_cmd_take(cmd, buf, 1, 1)))
	{
		tcsetattr(0, TCSANOW, &termios2);
		return (-1);
	}
	tcsetattr(0, TCSANOW, &termios2);
	if (!(str = ft_remove_slash(str, -1)))
		return (-1);
	ft_putstrfd(pipe[1], str);
	write(pipe[1], "\n", 1);
	write(1, "\n", 1);
	return (0);
}
