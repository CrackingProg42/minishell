/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:19:51 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/15 14:48:52 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	signal(SIGQUIT, ft_sigquit); // ctrl + '\' 
	signal(SIGINT, ft_sig); // ctrl + c 
	ft_child(envp);
	system("leaks a.out");
	return (0);
}

