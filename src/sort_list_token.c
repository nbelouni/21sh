/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:05:01 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:10:12 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_find_fd(t_token *list)
{
	char	*s;

	s = NULL;
	if (list && list->word && !ft_atoi(list->word) &&
		ft_strcmp(list->word, "0") != 0)
	{
		free(list->word);
		list->word = NULL;
	}
	return (1);
}

/*
**Faut faire des check avant de trier la liste, pour l'instant on garde ca
*/

int		create_cmd(t_token **list)
{
	t_token		*tmp;
	int			ret;

	ret = 1;
	if ((*list)->prev && (PREVISCMD((*list)) || (*list)->prev->type == TARGET))
		return (1);
	tmp = ft_tokenew(CMD, NULL);
	if ((*list)->prev)
	{
		(*list)->prev->next = tmp;
		tmp->prev = (*list)->prev;
		ret = 0;
	}
	(*list)->prev = tmp;
	tmp->next = (*list);
	return (ret);
}

void	sort_list_token(t_token **list, t_completion *completion, t_lst *hist)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		if (elem->type == FD_IN)
			(ft_swap_in(&elem) ? *list : (*list = elem));
		if (is_dir_type(elem->type) && ft_find_fd(elem))
			create_cmd(&elem) ? *list : (*list = elem);
		if (ISAMP(elem) && elem->next && check_error_out(elem->next))
			return ;
		if ((ISREDIR(elem->type)) && elem->next && elem->next->type == CMD)
			elem->next->type = TARGET;
		if (elem->type == TARGET && elem->next && NEXTISCMD(elem))
			check_target_place(&elem);
		if (elem->type == CMD && elem->prev && PREVISCMD(elem))
			elem->type = ARG;
		if (elem->type == CMD)
			elem = is_local_var(elem);
		if (elem->type == DL_DIR)
			here_doc(elem->next, completion, hist);
		elem = elem->next;
	}
	while ((*list) && (*list)->prev)
		(*list) = (*list)->prev;
}
