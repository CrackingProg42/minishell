#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../mylibft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# define TRUE 1
# define FALSE 0

typedef struct		s_redirection
{
	int				in;
	int 			putfile;
	int 			putendfile;
	char			*file;
}					t_redirection;

typedef struct		s_quotes
{
	int				q;
	int				dq;
}					t_quotes;

int 				split_semicol(char *cmd, char **env);
int 				split_pipes(char *cmd, char ***env);
char				**free_tab(char **tab);
void 				execcmd(char *cmd, char ***env);
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s, char const *set);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char                **ft_split_with_quote(char const *s, char c);
int 				execcmd_parent(char *cmd, char ***env);
char 				*ft_get_env(char **env, char *var);
int     			ft_lstlen(char **lst);

#endif