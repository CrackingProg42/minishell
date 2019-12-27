/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:19:51 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/27 10:31:08 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_trie(char **str)
{
	int i;
	char *tmp;

	i = 0;
	while (str[i + 1])
	{
		if (ft_cmp(str[i], str[i +1]) > 0)
		{
			tmp = str[i];
			str[i] = str[i +1];
			str[i + 1] = tmp;
			i  = 0;
		}
		else
			i++;
	}
	return (str);
}

char **ft_copy_envp(char **envp)
{
	char **new;
	int i;

	i = 0;
	while (envp[i])
		i++;
	if (!(new = malloc(sizeof(char **) * (i + 1))))
		return (0);
	i = -1;
	while (envp[++i])
		if (!(new[i] = ft_strdup(envp[i])))
				return (0);
	new[i] = NULL;
	return (new);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env env;
	
	env.local = malloc(1);
	env.local[0] = NULL;
	g_dollar = 0;
	if (!(env.envp = ft_copy_envp(envp)))
		return (0);
	signal(SIGQUIT, ft_sigquit); // ctrl + '\' 
	ft_child(&env);
	ft_free_2tab(env.local, env.envp, 0);
	system("leaks a.out");
	return (0);
}

