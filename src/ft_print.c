/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 20:44:31 by alallema          #+#    #+#             */
/*   Updated: 2017/04/14 22:58:13 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** fonction de debug pour affichage de la liste chainee
*/

static char		*(tab_name[20]) = {
	[NO_TOKEN] = "NO_TOKEN",
	[CMD] = "CMD",
	[ESPACE] = "ESPACE",
	[DOT] = "DOT",
	[PIPE] = "PIPE,",
	[START] = "START",
	[SL_DIR] = "SL_DIR",
	[SR_DIR] = "SR_DIR",
	[OR] = "OR",
	[AND] = "AND",
	[DL_DIR] = "DL_DIR",
	[DR_DIR] = "DR_DIR",
	[LR_DIR] = "LR_DIR",
	[DIR_L_AMP] = "DIR_L_AMP",
	[DIR_R_AMP] = "DIR_R_AMP",
	[FD_IN] = "FD_IN",
	[TARGET] = "TARGET",
	[ARG] = "ARG"
};

void		ft_print_token_list(t_token **list)
{
	t_token		*elem;

	elem = *list;
	while (elem)
	{
		PUT2("--LIST--\n");
		if (elem && elem->word)
			PUT2("token :");PUT2(elem->word);X('\n');
		PUT2("type :");PUT2(tab_name[elem->type]);X('\n');
		PUT2("____________\n");
		elem = elem->next;
	}
}

/*
void		print_job(t_job *list)
{
	t_job		*job;
	t_process	*process;
	int			i;
	int			j;

	i = 1;
	j = 1;
	job = list;
	process = NULL;
	job = list;
	while (job)
	{
		process = job->process;
		PUT2("\n--- job");
		E(i);
		PUT2("--\n");
		while (process)
		{
			PUT2("\n--- process ");
			E(j);
			PUT2(process->cmd[0]);
			PUT2("--\n");
			process = process->next;
			j++;
		}
		i++;
		job = job->next;
	}
}*/
