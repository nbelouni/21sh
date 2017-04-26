/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:07:29 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:10:07 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_cmd	*ft_cmdnew(int token, char *cmd)
{
	t_cmd	*elem;

	if (!(elem = ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	if (cmd == NULL)
	{
		elem->token = token;
		elem->s = NULL;
	}
	else
	{
		elem->s = cmd;
		elem->token = token;
	}
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}
