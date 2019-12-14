/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paszhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:18:55 by paszhang          #+#    #+#             */
/*   Updated: 2019/12/14 23:31:37 by paszhang         ###   ########.fr       */
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

typedef	struct	s_list
{
	char *cmd;
	char *arg;
}				t_list;

pid_t g_pid;
pid_t g_child;

int	ft_stupid(int pipe);























//ft_child
int		ft_child(char **envp);

//ft_fonction 
int		ft_fonction(char *str, char ** envp, char cara);

//ft_split
int		compare(char str, char charset);
char	**ft_split(char *str, char charset);

// ft_error
void	ft_invalidcmd(char *str, int mode, char **envp);
void	ft_cd_error(char *str, int mode, char **envp);

//	ft_get_next_line
int		get_next_line(int fd, char **line);
char	*ft_save_rest(char *str1, char *str2);

//   ft_echo
void	ft_echo(char *str ,char **envp);
int		ft_check_quote(char *str);
char 	*ft_get_str(char *str, int quote ,int dquote, int fd);
void	ft_print_echo(char *str, char **envp, int i);

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

//variable
int		ft_variable(char *str, int *a, char ** envp);

// ft_signal.c
void	ft_sigquit(int a);
void	ft_sig(int a);
void	ft_dummit(int a);
#endif
