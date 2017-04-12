/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 19:25:07 by alallema          #+#    #+#             */
/*   Updated: 2017/02/22 13:43:43 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size, int i)
{
	t_list *elem;

	elem = (t_list*)malloc(sizeof(t_list));
	if (elem == NULL)
		return (NULL);
	if (content == NULL)
	{
		elem->content = NULL;
		elem->content_size = 0;
		elem->i = 0;
	}
	else
	{
		elem->content = ft_memalloc(content_size);
		if (elem->content == NULL)
			return (NULL);
		ft_memcpy(elem->content, content, content_size);
		elem->content_size = content_size;
		elem->i = i;
	}
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
