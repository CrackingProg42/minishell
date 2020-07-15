/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfeuilla <qfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:05:40 by qfeuilla          #+#    #+#             */
/*   Updated: 2019/10/23 14:16:42 by qfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*tmp;

	if (new && alst)
	{
		tmp = *alst;
		if (!tmp)
			(*alst) = new;
		else
		{
			tmp = ft_lstlast(tmp);
			tmp->next = new;
		}
	}
}
