/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concordance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:55:41 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/22 12:06:25 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmp_quote(char *str1, char *str2)
{
	int quote;
	int dquote;
	int i;

	dquote = 1;
	quote = 1;
	i = 0;
	while(str1[i] == ' ')
		i++;
	str1[i] == '\'' && dquote == 1 ? quote *= -1 : 0;
	str1[i] == '\"' && quote == 1 ? dquote *= -1: 0;
	quote != 1 || dquote != 1 ? str1++ : 0;
	while(str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	if (quote == -1)
		return (str2[i] == '\0' && str1[i] == '\'' ? 1 : 0);
	if (dquote == -1)
		return (str2[i] == '\0' && str1[i] == '\"' ? 1 : 0);
	return (str2[i] == '\0' && (str1[i] == '\0' || str1[i] == ' ')) ? 1 : 0;
}


int		ft_printable(char *str, char **envp)
{
	if (ft_cmp_quote(str, "env"))
		exit (ft_env(envp));
	if (ft_cmp_quote(str, "echo")) 
		exit (ft_echo(str, envp));
	if (ft_cmp_quote(str, "pwd")) 
	{
		str = getcwd(NULL,0);
		ft_printf("%s\n",str);
		free(str);
		exit (0);
	}
	if (ft_cmp_quote(str, "$?"))
		exit ((ft_error_dollar()));
	ft_path(str, envp);
	while (*str == ' ')
		str++;
	if (*str != '\0')
		exit (127);
	exit (0);
}

int		ft_concordance(char *str, char ***envp)
{
	if (ft_cmp_quote(str, "cd")) 
		return (g_dollar = ft_cd(str, *envp));
	if (ft_cmp_quote(str, "export"))
		return (!(int)(*envp = ft_export(str, *envp)));
	if (ft_cmp_quote(str, "unset")) 
		return (g_dollar = ft_unset(str, *envp));
	if (ft_cmp_quote(str, "exit")) 
		exit(0);
	return (1);
}
