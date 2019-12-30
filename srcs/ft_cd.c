/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:40:58 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/28 12:02:57 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_go_home(char **envp)
{
	char *home;

	if (!(home = ft_found_path(envp, "HOME")))
		return (0);
	chdir(home);
	return (0);
}

int		ft_cd(char *str, t_env *env)
{
	int ret;

	str += ft_echo_position(str);
	while (*str == ' ')
		str++;
	if (*str == '\0')
		return (ft_go_home(env->envp));
	ret = chdir(str);
	ret == -1 ? ft_cd_error(str, 0) : 0;
	return (0);
}
