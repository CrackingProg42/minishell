/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:18:55 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/27 11:04:18 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <errno.h> 
#include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <stdarg.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <termios.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <term.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdarg.h>
# include <stdint.h>
#include <curses.h>
#include <term.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <term.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdarg.h>
# include <stdint.h>
#include <stdlib.h>

#include <curses.h>
#include <term.h>
# define BUFSIZE 4

typedef	struct s_env
{
	char **envp;
	char **local;
}				t_env;



typedef struct s_cmd
{
	char *str;
	int len;
	int posi;
	int gau;
	int dro;
	int aff;
	int affpo;
}				t_cmd;


typedef	struct	s_redir
{
	char *path;
	int in;
	int putfile;
	int putendfile;
}				t_redir;

pid_t g_pid;
pid_t g_child;

char *g_str;
char g_dollar;


char 	*ft_rm_quote(char *str);
void	ft_rm_split_quote(char **str);

//ft_env
int 	ft_env(char **envp);
//ft_export
int	ft_export(char *str, t_env *env);
char **ft_new_envp(char **envp, char*new);
//ft_unset 
int	ft_unset(char *str, t_env *env);
//ft_cd
int		ft_cd(char *str, t_env *env);

//ft_path
int	ft_path(char *str, char **envp);
char 	*ft_found_path(char **envp, char *need);

//ft_annexe_quentin
char		*ft_join(char *str1, char *str2);
int			ft_strlen(char *s);

//jump_to_cara
int		ft_jump_space(char *str);
int		ft_jump_first_word(char *str);





//ft_redirection
int		ft_redirection(t_redir redir, int pipefd[2], int *save);

//ft_cut 
int		ft_cut_pipe(char *str, t_env *env);



//ft_cut_comma
int		ft_cut_comma(char *str, t_env *env);

// ft_get_cmd
int	ft_get_cmd(int pipe[2]);


// ft_check_pipe_redirection_comma
int		ft_check_if_pipe(char *str);
int		ft_check_if_comma(char *str);
t_redir ft_check_redirection(char *str);

//ft_fork
int     ft_fork(char **str,t_env *env);


//ft_concordance 

int		ft_concordance(char *str, t_env *env);
int		ft_printable(char *str, t_env *env);

//ft_child
int		ft_child(t_env *env);

//ft_cut_comma 
int		ft_cut_comma(char *str, t_env *env);

//ft_split
int		compare(char str, char charset);
char	**ft_split(char *str, char charset);

// ft_error
int		ft_invalidcmd(char *str, int mode, t_env *env);
void	ft_cd_error(char *str, int mode, t_env *env);
int		ft_error_dollar(void);
//	ft_get_next_line
char	*ft_save_rest(char *str1, char *str2);

//ft_free
int		ft_free_2d(char **str);
int 	ft_free(char *str);
int	ft_free_minus(char *str);
int		ft_free_2tab(char **str1, char **str2i, int ret);
//   ft_echo
int	ft_echo(char *str , t_env *env);
int		ft_check_quote(char *str);
char 	*ft_get_str(int quote ,int dquote, int fd);
void	ft_print_echo(char *str, t_env *env, int i);
int		ft_echo_position(char *str);

// ft_print
void	ft_print_header(void);
void	ft_home(void);
void	ft_print_2d(char **str);
//ft_printf
int		ft_printf(char *str, ...);

//annexe
void	ft_putstrfd(int fd, char *str);
int		ft_cmp_tospace(char *str1, char *str2);
int		ft_cmp(char *str1, char *str2);
char 	*ft_strneedel(char *src, char *need);
int		ft_free_2d(char **str);
char 	*ft_dup_to_space(char *str);
char	*ft_strtrim(char *s1, char const *set);
int		ft_lenght_to_cara(char *str, char cara);
int		ft_cmp_to_cara(char *str1, char *str2, char c);
char	*ft_strneedel_cara(char *src, char *need, char cara);
char	*ft_strdup(const char *s1);
void	ft_close_pipe(int pipefd[2]);
void	ft_putstr(char *str);
char **ft_trie(char **str);
char **ft_copy_envp(char **envp);

//variable
int		ft_variable(char *str, int *a, t_env *env, int *quote, int *dquote);

// ft_signal.c
void	ft_sigquit();
void	ft_sig();
#endif
