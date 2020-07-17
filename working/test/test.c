/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:41:59 by frthierr          #+#    #+#             */
/*   Updated: 2020/07/16 18:48:08 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
    printf(table_to_string(av));
    printf("\n");
    cmd_to_rafter(&av);
    printf(table_to_string(av));
    printf("\n");
    return 0;
}
