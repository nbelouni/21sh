/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_post.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 17:34:19 by alallema          #+#    #+#             */
/*   Updated: 2017/01/06 16:17:35 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strchr_post(const char *s, int c)
{
	int		i;
	char	*s2;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != (const char)c && s[i])
		i++;
	if (s[i] && s[i] == (char)c)
	{
		i++;
		if (s[i] == '\0')
			return (NULL);
		s2 = ft_strsub(s, i, ft_strlen(s) - i);
		return ((char *)s2);
	}
	return (NULL);
}
