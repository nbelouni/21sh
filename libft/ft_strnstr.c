/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:57:01 by alallema          #+#    #+#             */
/*   Updated: 2015/11/27 10:48:48 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		while ((str[i] == to_find[j] || to_find[j] == '\0') && i < len)
		{
			i++;
			j++;
			if (to_find[j] == '\0')
				return ((char *)&str[i - j]);
		}
		i++;
	}
	return (NULL);
}
