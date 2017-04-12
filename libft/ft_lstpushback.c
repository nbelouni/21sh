/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 15:26:34 by alallema          #+#    #+#             */
/*   Updated: 2017/02/13 21:03:01 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **begin, void const *s, size_t s_size, int i)
{
	t_list	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	if (!elem->next)
	{
		elem->next = ft_lstnew(s, s_size, i);
		elem->next->prev = elem;
		return ;
	}
	else
	{
		elem->next = ft_lstnew(s, s_size, i);
		elem->next->prev = elem;
	}
	return ;
}
