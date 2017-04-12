/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:48:18 by alallema          #+#    #+#             */
/*   Updated: 2015/11/28 17:28:31 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s2;
	unsigned char	d;
	size_t			i;

	i = 0;
	s2 = (unsigned char *)s;
	d = (unsigned char)c;
	while (i < n && s2[i] != d)
		i++;
	if (i < n && s2[i] == d)
		return (&s2[i]);
	return (NULL);
}
