/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:48:01 by alallema          #+#    #+#             */
/*   Updated: 2015/11/28 18:09:27 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest2;
	char	*src2;

	dest2 = dest;
	src2 = (char *)src;
	if (src2 < dest2)
	{
		dest2 += n - 1;
		src2 += n - 1;
		while (n--)
		{
			*dest2 = *src2;
			dest2--;
			src2--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
