/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:15:59 by QFM               #+#    #+#             */
/*   Updated: 2019/12/15 13:35:10 by QFM              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		search_path(char *input, char **envp)
{
	
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
		search_path(input, envp);
}