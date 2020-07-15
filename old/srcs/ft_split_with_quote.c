/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:54:31 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/03/02 15:30:58 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int          count_words(char *s, char c)
{
    int count;
    t_quotes quote;

    quote.dq = -1;
    quote.q = -1;
    count = 0;
    while (*s)
    {
        *s == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
        *s == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
        while (*s && (*s == c) && quote.dq == -1 && quote.q == -1)
            s++;
        if (*s && (!(*s == c) || quote.dq == 1 || quote.q == 1))
        {
            count++;
            while (*s && (!(*s == c) || quote.dq == 1 || quote.q == 1)) {
                s++;
                *s == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
                *s == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
            }
        }
    }
    return (count);
}

static char         *ft_malloc_tab(char *s, char c)
{
    
    char        *tab;
    int         i;
    t_quotes     quote;
    int o;
	int a;

    a = 0;
    quote.dq = -1;
    quote.q = -1;
    i = 0;
    while (s[i] && (!(s[i] == c) || quote.dq == 1 || quote.q == 1)) {
        s[i] == '\'' && quote.dq == -1 ? quote.q *= -1 && (i - 1 >= 0 && s[i - 1] == '\\' ? 1 : (a = 1)) : 0;
        s[i] == '\"' && quote.q == -1 ? quote.dq *= -1 && (i - 1 >= 0 && s[i - 1] == '\\' ? 1: (a = 1)) : 0;
        i++;
    }
    if (!(tab = (char *)malloc(sizeof(char) * (i + (a ? -1 : 1) ))))
        return (NULL);
    i = 0;
    o = 0;
    while (s[i] && (!(s[i] == c) || quote.dq == 1 || quote.q == 1))
    {
        s[i] == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
        s[i] == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
        if ((s[i] != '\'' && s[i] != '\"' && 
			(s[i] != '\\' || !s[i + 1] ||
			(s[i + 1] != '\'' && s[i + 1] != '\"'
			&& !(ft_isprint(s[i + 1]) && !a && (quote.dq == 1 || quote.q == 1))))) ||
			(i - 1 >= 0 && s[i - 1] == '\\')) {
            tab[o++] = s[i];
        }
        i++;
    }
    tab[i] = '\0';
    return (tab);
}

char                **ft_split_with_quote(char const *s, char c)
{
    char    **tab;
    char    *str;
    int     i;
    t_quotes     quote;

    quote.dq = -1;
    quote.q = -1;
    str = (char *)s;
    if (!(tab = (char **)malloc(sizeof(char*) * (count_words(str, c) + 1))))
        return (NULL);
    i = 0;
    while (*str)
    {
        *str == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
        *str == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
        while (*str && (*str == c) && quote.dq == -1 && quote.q == -1) {
            str++;
			*str == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
        	*str == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
		}
        if (*str && (!(*str == c) || quote.dq == 1 || quote.q == 1))
        {
            if (!(tab[i++] = ft_malloc_tab(str, c)))
                return (free_tab(tab));
            while (*str && (!(*str == c) || quote.dq == 1 || quote.q == 1)){
                str++;
                *str == '\'' && quote.dq == -1 ? quote.q *= -1 : 0;
                *str == '\"' && quote.q == -1 ? quote.dq *= -1 : 0;
            }
        }
    }
    tab[i] = 0;
    return (tab);
}