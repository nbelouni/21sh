/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:25:19 by alallema          #+#    #+#             */
/*   Updated: 2015/12/02 15:41:59 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_a(int n)
{
	int		i;

	i = 0;
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	ft_power(int i)
{
	int		div;

	div = 1;
	while (i > 0)
	{
		div = div * 10;
		i--;
	}
	return (div);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*s;
	int		div;

	i = ft_count_a(n);
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (s == NULL)
		return (NULL);
	div = ft_power(i - 1);
	i = 0;
	if (n == -2147483648)
		return (ft_strcpy(s, "-2147483648"));
	if (n < 0)
	{
		s[i++] = '-';
		n = -n;
	}
	while (div > 0)
	{
		s[i] = (n / div % 10 + 48);
		i++;
		div = div / 10;
	}
	s[i] = '\0';
	return (s);
}
