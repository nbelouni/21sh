/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 01:14:11 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/09 21:20:16 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new;
	size_t			i;

	i = 0;
	if (!s)
	{
		if (!(new = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
	}
	else
	{
		if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
	}
	while (s && s[start] && i < len)
	{
		new[i] = s[start];
		start++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
