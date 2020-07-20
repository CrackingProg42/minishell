/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:12:42 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/20 19:53:13 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# define ERR_READLINE "an error has occured while reading input"

# define ERR_UNFINISHED_QUOTE "quote was not proprely closed"

# define ERR_UNEXPECTED_TOKEN "syntax error near unexpected token"

# define ERR_UNKNOWN_COMMAND "unknown command"

# define ERR_PID "error creating new process"

# define ERR_EXECVE "error executing command"

# define ERR_TOO_MANY_ARGS "too many arguments"

# define ERR_PIPE "minishell: Syntax error: \"|\" unexpected"

# define ERR_REDIR "syntax error near unexpected token \"newline\""

#endif
