/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 19:56:20 by alallema          #+#    #+#             */
/*   Updated: 2015/12/02 11:07:56 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	**elem;
	t_list	*next;

	if (*alst != NULL && del != NULL)
	{
		elem = alst;
		while ((*elem)->next != NULL)
		{
			next = (*elem)->next;
			ft_lstdelone(elem, del);
			*elem = next;
		}
		ft_lstdelone(alst, del);
	}
}
