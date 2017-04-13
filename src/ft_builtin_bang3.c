/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_bang3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 22:08:24 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/13 22:40:07 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*find_number(char *s)
{
	int		i;

	i = 0;
	if (s[0] == '-')
		i += 1;
	if (!ft_isdigit(s[i]))
		return (NULL);
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (ft_strsub(s, 0, i));
		i++;
	}
	if (s[i - 1] < '9' && s[i - 1] > '0')
		return (ft_strdup(s));
	return (NULL);
}
