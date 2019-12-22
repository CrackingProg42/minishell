#include "minishell.h"


int		ft_check_fonc(char *str, char **envp)
{
	int status;

	if (ft_cmp(str, "env"))
		return (0);
	if (ft_cmp(str, "echo"))
		return (0);
	if (ft_cmp(str, "pwd"))
		return (0);
	if (ft_cmp(str, "$?"))
		return (0);
	if((g_child = fork()) == 0)
	{
		close(1);
		if(ft_path(str, envp))
			exit (-1);
	}
	waitpid(g_child, &status,0);
	if (!(WIFEXITED(status) && WEXITSTATUS(status) == 255))
		return (g_dollar = 0);
	while (*str == ' ')
		str++;
	if (*str == '\0')
		return (0);
	return ((g_dollar = ft_invalidcmd(str, 0, envp)));
}
