/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:05:40 by qfeuilla          #+#    #+#             */
/*   Updated: 2020/03/02 11:55:02 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int          count_words(char *s, char c)
{
    int count;
    count = 0;
    while (*s)
    {
        while (*s && (*s == c))
            s++;
        if (*s && !(*s == c))
        {
            count++;
            while (*s && !(*s == c))
                s++;
        }
    }
    return (count);
}

static char         *ft_malloc_tab(char *s, char c)
{
    char    *tab;
    int     i;
    i = 0;
    while (s[i] && !(s[i] == c))
        i++;
    if (!(tab = (char *)malloc(sizeof(char) * (i + 1))))
        return (NULL);
    i = 0;
    while (s[i] && !(s[i] == c))
    {
        tab[i] = s[i];
        i++;
    }
    tab[i] = '\0';
    return (tab);
}

char                **ft_split(char const *s, char c)
{
    char    **tab;
    char    *str;
    int     i;
    str = (char *)s;
    if (!(tab = (char **)malloc(sizeof(char*) * (count_words(str, c) + 1))))
        return (NULL);
    i = 0;
    while (*str)
    {
        while (*str && (*str == c))
            str++;
        if (*str && !(*str == c))
        {
            if (!(tab[i++] = ft_malloc_tab(str, c)))
                return (free_tab(tab));
            while (*str && !(*str == c))
                str++;
        }
    }
    tab[i] = 0;
    return (tab);
}