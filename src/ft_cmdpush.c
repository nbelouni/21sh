/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:07:27 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:10:07 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_cmdpush(t_cmd **begin, t_cmd *new)
{
	t_cmd	*elem;

	elem = *begin;
	if (elem == NULL)
		return ;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
	new->prev = elem;
}
