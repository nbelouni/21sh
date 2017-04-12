/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base16.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 12:36:43 by alallema          #+#    #+#             */
/*   Updated: 2016/04/30 16:26:37 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_atoi_base16(const char *str)
{
	int		i;
	int		nb;
	int		neg;

	neg = 1;
	nb = 0;
	i = 0;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			nb = (str[i] - 48) + (16 * nb);
		else if (str[i] >= 'a' && str[i] <= 'f')
			nb = (str[i] - 97 + 10) + (16 * nb);
		else if (str[i] >= 'A' && str[i] <= 'F')
			nb = (str[i] - 65 + 10) + (16 * nb);
		else
			return (nb * neg);
		i++;
	}
	nb = nb * neg;
	return (nb);
}
