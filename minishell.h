/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:02:46 by qfeuilla          #+#    #+#             */
/*   Updated: 2019/12/19 15:34:58 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>

char					g_dollar;
pid_t					g_pid;
pid_t					g_child;

int						ft_child(char **envp);

void					ft_sigquit();
void					ft_sig();

#endif