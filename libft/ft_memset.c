/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:45:30 by alallema          #+#    #+#             */
/*   Updated: 2015/12/02 11:12:44 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*src;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	if (n == 0)
		return (s);
	src = (unsigned char *)s;
	while (i < n)
	{
		src[i] = c;
		i++;
	}
	return (src);
}
