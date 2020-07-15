/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:08:06 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/03/05 13:41:54 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char 	*ft_get_env(char **env, char *var) {
	int		i;
	char 	**val;
	char	*ret;

	i = 0;
	while (env[i]) {
		val = ft_split(env[i], '=');
		if (!ft_strncmp(val[0], var, ft_strlen(var))) {
			ret = ft_strdup(val[1]);
			free_tab(val);
			return (ret);
		}
		free_tab(val);
		i++;
	}
	return (NULL);
}