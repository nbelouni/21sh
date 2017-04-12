/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:54:51 by alallema          #+#    #+#             */
/*   Updated: 2015/11/26 19:31:20 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t size)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(dest);
	if (size < len)
		return (ft_strlen(src) + size);
	while (i < size - len)
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[size - 1] = '\0';
	return (ft_strlen(src) + len);
}
