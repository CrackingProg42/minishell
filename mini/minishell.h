/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:18:55 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/17 14:47:28 by paszhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <stdarg.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>

# define BUFFER_SIZE 1

enum {ECHO, CD, PWD, EXPORT, UNSET, ENV, EXIT}; 

typedef	struct	s_redir
{
	char *path;
	int in;
	int putfile;
	int putendfile;
}				t_redir;

pid_t g_pid;
pid_t g_child;

//ft_env
int 	ft_env(char **envp);
char **ft_export(char *str, char **envp);
















//ft_redirection
int		ft_redirection(t_redir redir, int pipefd[2], int *save);

//ft_cut 
int		ft_cut_pipe(char *str, char ***envp);



//ft_cut_comma
int		ft_cut_comma(char *str, char ***envp);

// ft_get_cmd
int	ft_get_cmd(int pipe);


// ft_check_pipe_redirection_comma
int		ft_check_if_pipe(char *str);
int		ft_check_if_comma(char *str);
t_redir ft_check_redirection(char *str);

//ft_fork
int     ft_fork(char **str,char ***envp);


//ft_concordance 

int		ft_concordance(char *str, char ***envp, int mode);
int		ft_concordance2(char *str, char **envp, int mode);

//ft_child
int		ft_child(char **envp);

//ft_cut_comma 
int		ft_cut_comma(char *str, char ***envp);

//ft_split
int		compare(char str, char charset);
char	**ft_split(char *str, char charset);

// ft_error
int		ft_invalidcmd(char *str, int mode, char **envp);
void	ft_cd_error(char *str, int mode, char **envp);

//	ft_get_next_line
char	*ft_save_rest(char *str1, char *str2);

//ft_free
int		ft_free_2d(char **str);
int 	ft_free(char *str);

//   ft_echo
void	ft_echo(char *str ,char **envp);
int		ft_check_quote(char *str);
char 	*ft_get_str(int quote ,int dquote, int fd);
void	ft_print_echo(char *str, char **envp, int i);
int		ft_echo_position(char *str);

// ft_print
void	ft_print_header(void);
void	ft_home(void);

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
//variable
int		ft_variable(char *str, int *a, char ** envp);

// ft_signal.c
void	ft_sigquit(int a);
void	ft_sig(int a);
void	ft_dummit(int a);
#endif
