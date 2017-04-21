/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:06:12 by alallema          #+#    #+#             */
/*   Updated: 2017/04/21 18:12:45 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** fonction qui va chercher le bon element dans la list
** recursive lorsqu'il trouve plus d'element et que le bt
** ou bc lvl est incrementer
*/

t_token			*search_toke(t_token *lst)
{
	t_token	*tmp;
	t_token	*node_lst;
	int		first_time;

	tmp = lst;
	first_time = 0;
	node_lst = NULL;
	if (lst == NULL)
		return (NULL);
	if (tmp->select == 1)
		tmp = tmp->next;
	while (tmp && tmp->select == 0)
	{
		if (first_time == 0)
		{
			first_time = 1;
		}
		if (priority(node_lst, tmp))
			node_lst = tmp;
		tmp = tmp->next;
	}
	return (node_lst);
}

/*
** remonte la liste
*/

t_token			*search_toke_prev(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	if (lst == NULL)
		return (NULL);
	if (tmp->select == 1)
		tmp = tmp->prev;
	while (tmp && tmp->prev && tmp->select == 0)
		tmp = tmp->prev;
	return (search_toke(tmp));
}

/*
** cree le char **  ex: ls -la tmp
*/

void			cmd_len(t_token *lst, int *i, int *j)
{
	t_token	*tmp;
	int		tmpi;

	tmp = lst;
	tmpi = 0;
	while (tmp && (tmp->type == CMD || tmp->type == ARG))
	{
		if ((tmpi = ft_strlen(tmp->word)) >= *j)
			*j = tmpi;
		*i = *i + 1;
		tmp = tmp->next;
	}
}

char			**concate_cmd(t_token *lst)
{
	t_token	*tmp;
	int		i;
	int		j;
	int		count;
	char	**argv;

	tmp = lst;
	count = 0;
	i = 0;
	j = 0;
	cmd_len(tmp, &i, &j);
	argv = NULL;
	if (!(argv = (char **)malloc(sizeof(char*) * (i * j + 1))))
		return (NULL);
	argv[i * j] = NULL;
	while (tmp && tmp->word && (count <= i - 1))
	{
		argv[count] = ft_strdup(tmp->word);
		++count;
		tmp->select = 1;
		tmp = tmp->next;
	}
	argv[count] = NULL;
	return (argv);
}

/*
** print le char ** pour le debug
*/

void			print_tab(char **tabol)
{
	int		i;

	i = 0;
	while (tabol[i] != NULL)
	{
		PUT2(tabol[i]);
		PUT2("   ");
		++i;
	}
}
