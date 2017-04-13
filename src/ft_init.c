/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:13:58 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/13 17:46:52 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	ft_init_set initialise une nouvelle liste en l'allouant et en mettant tous
**	ses octets a 0, puis retourne la nouvelle liste de type set.
*/

t_core		*ft_init_core(void)
{
	t_core			*set;

	set = NULL;
	if ((set = malloc(sizeof(t_core))) == NULL)
		return (NULL);
	set->env = NULL;
	set->set = NULL;
	set->exp = NULL;
	set->hist = NULL;
	return (set);
}

/*
**	ft_init_list initialise une nouvelle liste en l'allouant et en mettant tous
**	ses octets a 0, puis retourne la nouvelle liste de type env.
*/

t_lst		*ft_init_list(void)
{
	t_lst		*lst;

	lst = NULL;
	lst = malloc(sizeof(t_lst));
	if (lst == NULL)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	lst->size = 0;
	return (lst);
}

/*
**	ft_init_elem initialise un nouvel element en l'allouant et en mettant tous
**	ses octets a 0, puis retourne le nouvel element.
*/

t_elem		*ft_init_elem(void)
{
	t_elem		*elem;

	elem = NULL;
	if ((elem = malloc(sizeof(t_elem))) == NULL)
	{
		return (NULL);
	}
	elem->is_modified = 0;
	elem->is_appended = 0;
	elem->name = NULL;
	elem->value = NULL;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
