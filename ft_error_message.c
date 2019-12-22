/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:47:36 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/22 11:32:43 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error_dollar()
{
	ft_printf("\033[32mminishell\033[0m: command not foud : %d\n",g_dollar);
	return (127);
}

int		ft_invalidcmd(char *str, int mode, char **envp)
{
	int i;
	
	i = 0;
	str += ft_jump_space(str);
	if (!(str[0] == '$' && str[1] == '?' && str[2] == '\0'))
	{
		i = ft_jump_first_word(&str[i]);
		mode == 0 && i != 0 ?  str[i] = '\0' : 0;
		mode == 0 ? ft_printf("\033[32mminishell\033[0m: command not foud : ") : 0;
		mode == 0 ?	ft_print_echo(str, envp ,0) : 0;
		mode == 1 ? ft_printf("\033[32mminishell\033[0m: parse error near `<' or '>'") : 0;
		mode == 2 ? ft_printf("\033[32mminishell\033[0m: export: not valid in this context") : 0;
		write(1, "\n", 1);
	}
	return (1);
}

void	ft_cd_error(char *str, int mode, char **envp)
{
	if (mode == 0)
		ft_printf("\033[32mminishell\033[0m: cd: no such file or directory : ");
	if (mode == 1)
		ft_printf("\033[32mminishell\033[0m: cd: not a directory : ");
		ft_print_echo(str, envp, 0);
		write(1, "\n", 1);
}
