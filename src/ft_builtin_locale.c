/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_locale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:07:54 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:10:07 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_builtin_locale(t_core *core, char **args)
{
	if (args == NULL || args[0] == NULL)
	{
		if (core != NULL && core->set != NULL && core->set->head != NULL)
		{
			ft_print_lst(core->set);
		}
	}
	return (0);
}
