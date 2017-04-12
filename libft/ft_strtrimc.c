/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 16:52:54 by alallema          #+#    #+#             */
/*   Updated: 2016/04/22 17:05:12 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrimc(char const *s, char c)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	len = ft_strlen((char *)s) - 1;
	if (i <= len)
	{
		while (s[len] && s[len] == c)
			len--;
	}
	str = (char *)malloc(sizeof(char) * ((len - i) + 2));
	if (str == NULL || i == (len + 1))
		return (ft_strdup(""));
	while (i <= len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
