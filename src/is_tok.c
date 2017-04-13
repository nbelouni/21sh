/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:02:54 by alallema          #+#    #+#             */
/*   Updated: 2017/04/13 17:46:53 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		cut_space(char *s, int i)
{
	while (is_space(s, i) == ESPACE)
		i++;
	return (i);
}

int		is_brace(char *s, int i)
{
	(void)s;
	(void)i;
	return (0);
}

int		is_space(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == ' ')
			return (ESPACE);
	}
	return (0);
}

int		is_dot(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == ';')
			return (DOT);
	}
	return (0);
}
