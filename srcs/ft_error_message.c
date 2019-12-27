/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:47:36 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/26 17:20:46 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error_dollar()
{
	ft_printf("\033[32mminishell\033[0m: command not foud : %d\n",g_dollar);
	return (127);
}

void	ft_print_local(char **local1)
{
	int i;
	char **local;

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
		mode == 0 && i != 0 ?  str[i] = '\0' : 0;
		mode == 0 ? ft_printf("\033[32mminishell\033[0m: command not foud : ") : 0;
		mode == 0 ?	ft_print_echo(str, env ,0) : 0;
		mode == 0 ?	ft_print_echo("\n", env ,0) : 0;
		mode == 1 ? ft_printf("\033[32mminishell\033[0m: parse error near `<' or '>'\n") : 0;
		mode == 2 ? ft_printf("\033[32mminishell\033[0m: export: not valid in this context\n") : 0;
		mode == 3 ? ft_printf("\n\033[32mminishell\033[0m: parse error near `|'") : 0;
		mode == 4 ? ft_print_local(env->envp) : 0;
	}
	return (1);
}

void	ft_cd_error(char *str, int mode, t_env *env)
{
	if (mode == 0)
		ft_printf("\033[32mminishell\033[0m: cd: no such file or directory : ");
	if (mode == 1)
		ft_printf("\033[32mminishell\033[0m: cd: not a directory : ");
		ft_print_echo(str, env, 0);
		write(1, "\n", 1);
}
