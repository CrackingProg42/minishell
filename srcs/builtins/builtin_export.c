/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:25:27 by frthierr          #+#    #+#             */
/*   Updated: 2020/08/05 16:52:28 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			export_envvar(int i, char **argv)
{
	char	*var;
	int		syntax_check;
	int		return_value;
	char	*to_free;

	if ((syntax_check = export_check_syntax(argv[i])) == 1)
		return (1);
	if (syntax_check == 3 && !(argv[i] = added_var(argv[i])))
		return (1);
	else if (syntax_check == 2)
		return (0);
	if (!(var = ft_strndup(argv[i], ft_strlen_char(argv[i], '='))))
		return (1);
	if (!(to_free = get_env(var)))
		return_value = new_env_var(argv[i]);
	else
	{
		free(to_free);
		return_value = modify_env_var(i, argv, var);
	}
	free(var);
	return (return_value);
}

int			all_env_written(char *env_written, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (!env_written[i++])
			return (0);
	}
	return (1);
}

char		*ft_quote_string(char *str)
{
	char	*qstr;
	int		i;

	i = 0;
	if (!(qstr = malloc(sizeof(char) * (ft_strlen(str) + 3))))
		return (NULL);
	qstr[0] = '\"';
	while (str[i++])
		qstr[i] = str[i - 1];
	qstr[i++] = '\"';
	qstr[i] = '\0';
	return (qstr);
}

char		*ft_quote_envvar(char *envvar)
{
	char	*head;
	char	*tail;
	char	*tmp;
	int		i;

	i = 0;
	if (!(head = malloc(sizeof(char) * ft_strlen(envvar))))
		return (NULL);
	while (envvar[i] && envvar[i] != '=')
	{
		head[i] = envvar[i];
		i++;
	}
	head[i++] = '=';
	head[i] = 0;
	if (!(tmp = ft_strdup(&envvar[i])))
		return (NULL);
	if (!(tail = ft_quote_string(tmp)))
		return (NULL);
	free(tmp);
	if (!(head = ft_strjoin_2free(head, tail)))
		return (NULL);
	return (head);
}

void		print_export_loop(char **env_written, size_t len)
{
	size_t	lowest_index;
	size_t	i;
	char	*quoted_string;

	while (!all_env_written(*env_written, len))
	{
		lowest_index = 0;
		while ((*env_written)[lowest_index])
			lowest_index++;
		i = 1;
		while (g_env[i])
		{
			if (!(*env_written)[i] && ft_strncmp(g_env[lowest_index],
							g_env[i], ft_strlen(g_env[lowest_index]) + 1) > 0)
				lowest_index = i;
			i++;
		}
		(*env_written)[lowest_index] = 1;
		if (!(quoted_string = ft_quote_envvar(g_env[lowest_index])))
			return ;
		ft_printf("declare -x %s\n", quoted_string);
		free(quoted_string);
	}
}

int			print_export(void)
{
	size_t	len;
	char	*env_written;

	len = 0;
	while (g_env[len])
		len++;
	if (!(env_written = (char*)malloc(sizeof(char) * (len))))
		return (1);
	ft_bzero(env_written, len);
	print_export_loop(&env_written, len);
	free(env_written);
	return (1);
}

int			builtin_export(char **argv)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!argv[1])
		return (print_export());
	while (argv[i])
	{
		if (export_envvar(i, argv))
			status = 1;
		i++;
	}
	return (status);
}
