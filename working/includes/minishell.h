/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:40:30 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/19 18:10:57 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../srcs/libft/libft.h"
# include "errors.h"
# include "colors.h"

# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

/*
**	DEFINES
*/

# define PROMPT_START_MSG "minishell$ "
# define PIPE_START_MSG "> "

# define MINISHELL_PATH "./minishell"

# define BUILTIN_CD 0
# define BUILTIN_EXIT 1
# define BUILTIN_PWD 2
# define BUILTIN_ENV 3
# define BUILTIN_ECHO 4	
# define BUILTIN_EXPORT 5
# define BUILTIN_UNSET 6

# define SAVE_POINTERS_TO_EXIT 0
# define EXIT_NOW 1

/*
**	 ________GLOBAL_VARIABLES________
*/

char			**g_env;
int				g_env_modified;
int				g_exit_status;
int				g_p_stop_sig;
int				open_pipe;
int				pipe_error;

/*
** ________FUNCTIONS________
*/

void			minishell_start();
char			*table_to_string(char **table);

/*
**       ______PARSING_AND_TOKENIZATION_____
*/

void			print_prompt();
t_list			*prompt_loop(int depth);
void			manage_quotes(char *quotes, char c);
int				isQuote(char c);
int				isSpecialChar(char *s);
char			*copy_token(char *str, size_t maxsize);
t_list			*tokenize(char *line);
size_t			get_token(char *tokenStart, t_list **tokenlist);
int				add_to_token_list(char *token, t_list **tokenlist);
size_t			tokenLen(char *tokenStart);
size_t			tokenLenSQuote(char *tokenStart);
size_t			tokenLenDQuote(char *tokenStart);
size_t			token_len_special(char *token_start);
int				tokens_syntax_check(t_list *token_list);
int				pipes_syntax_check(t_list *token_list);
char 			*last_token(t_list *tokenlist);

/*
**       ______TOKEN_EXPANSION_____
*/

char			*get_env(char *key);
int				ft_strlen_key(char *key_start);
char			*expand_env(char *token, char *final_token, int *i, int *j);
void			*get_final_token(void *content);
t_list			*expand_tokens(t_list *token_list);
char			*expand_token_quote(char *token);
char			*expand_token_noquote(char *token);
size_t			ft_strlen_etokens(char *s);
int				is_specialchar_dquote(char c);

/*
**		_____COMMANDS_____
*/

t_list			*get_command_list(t_list *token_list);
int				execute_commands(t_list **commandlist);
void			free_commandlist(t_list **commandlist);
void			exit_minishell(int action, t_list *token_list, t_list **commandlist, char ***args);
int				minishell_launch(char **argv, int *start, int islast);
char			*search_path(char *command);
int				execute_pipes(t_list **commandlist);

/*
**		_____BUILTINS_____
*/

int				is_builtin_child(char *command);
int				is_builtin_parent(char *command);
int				launch_builtin_child(int builtin_id, char **argv);
int				launch_builtin_parent(int builtin_id, char **argv);
int				builtin_cd(char **args);
int				builtin_exit(char **args);
int				builtin_pwd();
int				builtin_env();
int				builtin_echo(char **argv);
int				builtin_export(char **argv);
int				builtin_unset(char **argv);

/*
**		_____SIGNAL_HANDLING_____
*/

void			sigint_handler(int signo);
void			sigquit_handler(int sig);
void			signal_default();

/*
**		______UTILS______
*/

void			print_tokens(t_list *tokenlist);
void			print_argv(char **argv);
char			*remove_quotes(char *str);

/*
**		______STRUCTS______
*/

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

/*
**		_____REDIRECTION_____
*/

t_redirection	stock_redir(char *cmd);
int				redirection(t_redirection redir, int (*pipefd)[2], int *save);
void 			cmd_to_rafter(char ***cmd);

#endif
