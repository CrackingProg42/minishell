#include "../includes/minishell.h"

int main(int ac, char **av, char **envp) {
	split_semicol(av[1], envp);
	return (0);
}