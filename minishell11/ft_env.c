
#include "minishell.h"

int 	ft_env(char **envp)
{
	while (*envp)
		ft_printf("%s\n",*envp++);
	return (0);
}


