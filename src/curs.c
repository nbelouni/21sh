/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:25:06 by alallema          #+#    #+#             */
/*   Updated: 2017/04/25 22:57:19 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		clean_pos_curs(void)
{
	if (g_curs.win_col >= (int)get_prompt_len())
	{
		g_curs.col = get_prompt_len();
		g_curs.row = 0;
	}
	else
	{
		g_curs.row = get_prompt_len() / g_curs.win_col;
		g_curs.col = get_prompt_len() % g_curs.win_col;
	}
}

t_bool		init_curs(void)
{
	if (get_win() == FALSE)
		return (FALSE);
	clean_pos_curs();
	return (TRUE);
}

int			get_curs(void)
{
	return (g_curs.win_col * g_curs.row + g_curs.col);
}

int			get_curs_add(int n)
{
	return (g_curs.win_col * g_curs.row + g_curs.col + n);
}
