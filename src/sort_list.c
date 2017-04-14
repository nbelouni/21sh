/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:14:54 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/14 23:07:06 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_slist		*create_sort_list(char *s)
{
	t_slist	*elem;

	if (!s)
		return (NULL);
	if (!(elem = ft_memalloc(sizeof(t_slist))))
		return (NULL);
	elem->s = s;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void		push_sort_list(t_slist **begin, t_slist *new)
{
	t_slist	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
	new->prev = elem;
}

void		clear_sort_list(t_slist *cmd)
{
	if (cmd->s)
		free(cmd->s);
	cmd->s = NULL;
}

void		rm_sort_list(t_slist **cmd)
{
	t_slist	*tmp;
	t_slist	*elem;

	if (cmd == NULL)
		return ;
	elem = (*cmd)->prev;
	tmp = (*cmd)->next;
	if (!elem)
		*cmd = (*cmd)->next;
	else
	{
		elem->next = tmp;
		tmp->prev = elem;
	}
	ft_memdel((void *)cmd);
}

void		destroy_sort_list(t_slist **begin)
{
	t_slist	*tmp;
	t_slist	*list;

	list = *begin;
	tmp = NULL;
	while (list)
	{
		if (list->next)
			tmp = list->next;
		else
			tmp = NULL;
		clear_sort_list(list);
		free(list);
		list = tmp;
	}
	*begin = NULL;
}
