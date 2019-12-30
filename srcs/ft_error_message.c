/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:47:36 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 18:21:50 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error_redir(char *str, int mode)
{
	mode == 0 ? ft_putstr("\033[32mminishell\033[0m: p\
arse error near `<' or '>'\n") : 0;
	mode == 1 ? ft_putstr("\033[32mminishell\033[0m: n\
o such file or directory: ") : 0;
	mode == 1 ? ft_print_echo(str, 0) : 0;
	mode == 1 ? ft_putstr("\n") : 0;
	mode == 2 ? ft_putstr("\033[32mminishell\033[0m: error open file\n") : 0;
	return (ft_free(str));
}

int		ft_error_dollar(char *str)
{
	ft_putstr("\033[32mminishell\033[0m: command not foud : ");
	ft_putnbr(g_dollar);
	ft_print_to_space(str);
	write(1, "\n", 1);
	g_dollar = 127;
	return (127);
}

void	ft_print_local(char **local1)
{
	int i;
	char**local;

	i = 0;
	local = ft_copy_envp(local1);
	local = ft_trie(local);
	while (local[i])
	{
		ft_putstr(local[i++]);
		ft_putstr("\n");
	}
	ft_free_2d(local);
}

int		ft_invalidcmd(char *str, int mode, t_env *env)
{
	int i;

	i = 0;
	str += ft_jump_space(str);
	if (!(str[0] == '$' && str[1] == '?' && str[2] == '\0'))
	{
		i = ft_jump_first_word(&str[i]);
		mode == 0 && i != 0 ? str[i] = '\0' : 0;
		mode == 0 || mode == 5 ? ft_putstr("\033[32mminishell\033[0m: c\
ommand not foud : ") : 0;
		mode == 0 || mode == 5 ? ft_print_echo(str, 0) : 0;
		mode == 0 ? ft_print_echo("\n", 0) : 0;
		mode == 2 ? ft_putstr("\033[32mminishell\033[0m: export: n\
ot valid in this context\n") : 0;
		mode == 3 ? ft_putstr("\n\033[32mminishell\033[0m: p\
arse error near `|'") : 0;
		mode == 4 ? ft_print_local(env->envp) : 0;
	}
	return (1);
}

void	ft_cd_error(char *str, int mode)
{
	if (mode == 0)
		ft_putstr("\033[32mminishell\033[0m: cd: no such file or directory : ");
	if (mode == 1)
		ft_putstr("\033[32mminishell\033[0m: cd: not a directory : ");
	ft_print_echo(str, 0);
	write(1, "\n", 1);
}
