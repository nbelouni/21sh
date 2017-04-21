/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:16:59 by alallema          #+#    #+#             */
/*   Updated: 2017/04/21 18:19:01 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			free_content_ast(t_tree *node)
{
	if (node->cmd != NULL)
		ft_tabdel(node->cmd);
	node->cmd = NULL;
}

void			free_ast(t_tree *ast)
{
	if (!ast)
	{
		return ;
	}
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	free_content_ast(ast);
	free(ast);
}

void			ft_push_ast(t_token *list, t_tree **ast)
{
	t_tree	*head_node;

	if (list)
	{
		head_node = new_tree(list);
		*ast = head_node;
	}
}
