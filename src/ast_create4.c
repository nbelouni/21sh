/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:09:52 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:10:06 by nbelouni         ###   ########.fr       */
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
