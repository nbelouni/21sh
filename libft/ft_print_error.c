/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 18:29:55 by maissa-b          #+#    #+#             */
/*   Updated: 2017/02/08 14:56:16 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_error(char *cmd, char *err, int ret)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	return (ret);
}
