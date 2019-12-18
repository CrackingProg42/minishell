#include "minishell.h"

char 	*ft_found_path(char **envp)
{
	char *path;
	int i;
	
	i = 0;
	while (envp[i])	
		if ((path = ft_strneedel(envp[i++], "PATH")))
			break ;
	if (!path)
		return (0);
	return (path);
}
char **ft_prepare_str(char *str)
{
	char **dest;

	if (!(str = ft_strtrim(str, " ")))
		return (0);
	if (!(str = ft_join("/", str)))
		return (0);
	if (!(dest = ft_split(str, ' ')))
		return (0);
	return (dest);
}

void	ft_test_path(char *str, char **envp)
{		
	char **arg;	
	
	if (!(arg = ft_split(str, ' ')))
		return ;
	execve(arg[0], &arg[0], envp);
}

int	ft_path(char *str, char **envp)
{
	char *path;
	char **splitpath;
	char *prog;
	char **arg;	
	int i;

	ft_test_path(str, envp);
	if (!(path = ft_found_path(envp)))
		return (1);
	path++;
	if (!(splitpath = ft_split(path, ':')))
		return (1);
	if (!(arg = ft_prepare_str(str)))
		return (ft_free_2d(splitpath));
	path = arg[0];
	i = 0;
	while (splitpath[i])
	{
		if (!(arg[0] = ft_join(splitpath[i++], path)))
			return (ft_free_2d(splitpath));
		execve(arg[0], &arg[0], envp);
	}
	return (1);
}
