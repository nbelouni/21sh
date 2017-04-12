/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:53:55 by alallema          #+#    #+#             */
/*   Updated: 2015/11/27 11:15:46 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i])
	{
		while (str[i] == to_find[j] || to_find[j] == '\0')
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
