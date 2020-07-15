#include "../includes/minishell.h"

int split_semicol(char *cmd, char **env) {
	char **splt;
	int k;

	k = 0;
	splt = ft_split(cmd, ';');
	while (splt[k]) {
		split_pipes(splt[k], &env);
		k++;
	}
	free_tab(splt);
	return (0);
}