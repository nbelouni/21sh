/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:37:17 by alallema          #+#    #+#             */
/*   Updated: 2017/04/21 18:38:07 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	delete_process_tree_node(int type, void *data)
{
	if (!data)
		return ;
	if (type == IF)
		delete_condition_if(data);
	else
		delete_list((t_list **)&data, (void *)delete_process);
}

void	delete_tree(t_node_p summit_node, void (f)(int, void *))
{
	t_list	*stack;

	stack = NULL;
	while ((summit_node = iter_pre_order(summit_node, &stack)))
	{
		f(summit_node->type, delete_node(summit_node));
		summit_node = NULL;
	}
}

void	delete_job(t_job *j)
{
	delete_tree(j->process_tree, delete_process_tree_node);
	delete_list(&j->wait_process_list, (void *)delete_process);
	free(j);
}
