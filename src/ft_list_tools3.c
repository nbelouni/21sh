/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_tools3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:06:49 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:10:07 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	Ft_del_elem supprime un element de la liste ainsi que ses variables.
**	(cette fonction est une dumb function (se referer au README))
*/

void		ft_extract_elem(t_elem **elem, t_lst *lst)
{
	lst->size--;
	if ((*elem)->next != NULL && (*elem)->prev != NULL)
	{
		(*elem)->prev->next = (*elem)->next;
		(*elem)->next->prev = (*elem)->prev;
	}
	else if ((*elem)->next != NULL && (*elem)->prev == NULL)
	{
		lst->head = (*elem)->next;
		(*elem)->next->prev = NULL;
	}
	else if ((*elem)->next == NULL && (*elem)->prev != NULL)
	{
		lst->tail = (*elem)->prev;
		(*elem)->prev->next = NULL;
	}
	else if ((*elem)->next == NULL && (*elem)->prev == NULL)
	{
		lst->tail = NULL;
		lst->head = NULL;
	}
	(*elem)->next = NULL;
	(*elem)->prev = NULL;
}

/*
**	Ft_clear_elem va supprimer le contenu d'elem.
*/

void		ft_clear_elem(t_elem **elem)
{
	if ((*elem)->name != NULL)
	{
		ft_strdel(&((*elem)->name));
	}
	if ((*elem)->value != NULL)
	{
		ft_strdel(&((*elem)->value));
	}
	(*elem) ? free(*elem) : 0;
	*elem = NULL;
}

/*
**	Ft_del_elem retire le maillon de la liste, puis delete son contenu.
*/

void		ft_del_elem(t_elem **elem, t_lst *lst)
{
	ft_extract_elem(elem, lst);
	ft_clear_elem(elem);
}
