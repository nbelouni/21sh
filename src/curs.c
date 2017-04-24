/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:25:06 by alallema          #+#    #+#             */
/*   Updated: 2017/04/13 17:46:51 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		clean_pos_curs(void)
{
	g_curs.col = get_prompt_len();
	g_curs.row = 0;
}

t_bool		init_curs(void)
{
	if (get_win() == FALSE)
		return (FALSE);
	clean_pos_curs();
	return (TRUE);
}
