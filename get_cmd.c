/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:15:59 by QFM               #+#    #+#             */
/*   Updated: 2019/12/15 15:22:23 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_join(char *str1, char *str2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1))))
		return (NULL);
	while (str1[i])
		new[j++] = str1[i++];
	i = 0;
	while (str2[i])
		new[j++] = str2[i++];
	new[j] = '\0';
	return (new);
}

void		exec_intern_cmd(char *input, char **envp, char **cmd)
{
	if (ft_str_cmp(cmd[0],"echo") == 0)
		ft_echo(cmd, envp);
	else if (ft_str_cmp(cmd[0],"cd") == 0)
		ft_cd(cmd, envp);
	else if (ft_str_cmp(cmd[0],"pwd") == 0)
		ft_pwd(cmd, envp);
	else if (ft_str_cmp(cmd[0],"export") == 0)
		ft_export(cmd, envp);
	else if (ft_str_cmp(cmd[0],"unset") == 0)
		ft_unset(cmd, envp);
	else if (ft_str_cmp(cmd[0],"env") == 0)
		ft_env(cmd, envp);
	else if (ft_str_cmp(cmd[0],"exit") == 0)
		ft_exit(cmd, envp);
}

void		search_path(char *input, char **envp, char **cmd)
{
	char	*path;
	char	*tmp;
	char	**folders;
	int		i;

	i = 0;
	path = ft_strneedel(*envp, "PATH");
	while (path[i] != '\n' && path[i] != '\0')
		i++;
	tmp = &path[i];
	*tmp = '\0';
	folders = ft_split(path, ':');
	*tmp = '\n';
	i = 0;
	while (folders[i])
	{
		execve(ft_join(folders[i], cmd[0]), cmd, envp);
		i++;
	}
	ft_invalidcmd(input, envp);
}

void		get_cmd(char *input, char **envp)
{
	char	**cmd;

	cmd = split(input, ' ');
	if (ft_str_cmp(cmd[0],"echo") == 0 || ft_str_cmp(cmd[0],"cd") == 0 ||
		ft_str_cmp(cmd[0],"pwd") == 0 || ft_str_cmp(cmd[0],"export") == 0 ||
		ft_str_cmp(cmd[0],"unset") == 0 || ft_str_cmp(cmd[0],"env") == 0 ||
		ft_str_cmp(cmd[0],"exit") == 0)
		exec_intern_cmd(input, envp, cmd);
	else
		search_path(input, envp, cmd);
}