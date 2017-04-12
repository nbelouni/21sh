/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:47:33 by alallema          #+#    #+#             */
/*   Updated: 2015/12/02 17:59:06 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*dest2;
	char	*src2;
	size_t	i;

	i = 0;
	if (n == 0 || !src || !dest)
		return (NULL);
	dest2 = (char *)dest;
	src2 = (char *)src;
	while (i < n)
	{
		dest2[i] = src2[i];
		if (dest2[i] == (char)c)
			return ((void *)&dest2[i + 1]);
		i++;
	}
	return (NULL);
}
