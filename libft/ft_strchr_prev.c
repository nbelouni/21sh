/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_prev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 17:34:19 by alallema          #+#    #+#             */
/*   Updated: 2016/09/08 16:17:09 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr_prev(const char *s, int c)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = ft_strdup(s);
	while (s2[i] != (const char)c && s2[i])
		i++;
	if (s2[i] == (char)c && s2[i])
	{
		s2[i] = '\0';
		return ((char *)s2);
	}
	return (NULL);
}
