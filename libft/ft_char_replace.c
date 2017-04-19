/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:17:56 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/19 17:20:21 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void		ft_char_replace(char *s, char search, char replace)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == search)
			s[i] = replace;
	}
}
