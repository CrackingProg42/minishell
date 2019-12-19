/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:19:51 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/19 15:40:28 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *str)
{
	char *dest;
	int i;

	if (!(dest = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (0);
	i = -1;
	while (str[++i])
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
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
	
	g_dollar = 0;
	if (!(envp = ft_copy_envp(envp)))
		return (0);
	signal(SIGQUIT, ft_sigquit); // ctrl + '\' 
	signal(SIGINT, ft_sig); // ctrl + c 
	ft_child(envp);
	system("leaks a.out");
	return (0);
}

