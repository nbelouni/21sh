/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 17:21:39 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/13 17:58:25 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	ft_exec_history est une fonction qui va gerer le comportement du builtin
**	history selon les informations envoyés par ft_builtin_history.
**	Args est forcement non-NULL, on appelle donc ft_parse_histopt, le parseur
**	particulier d'options pour l'historique, qui va definir si il y a
**	des options ou des erreurs d'options. Sinon, ft_print_history est appellé
**	apres avoir checké qu'un digit est bien envoyé au builtin.
*/

static int	ft_exec_history(t_lst *set, t_lst *hist, char **args)
{
	int		ret;

	ret = (args[0][0] != '-') ? 1 : ft_parse_histopt(set, hist, args);
	if (ret == 0 || ret == ERR_NEW_CMD || ret == ERR_EXIT)
	{
		return (ret);
	}
	else
	{
		if (!ft_strisdigit(args[0]))
		{
			write(2, "history: ", 9);
			return (ft_print_error(args[0], ERR_NUM_ARG, ERR_NEW_CMD));
		}
		ft_print_history(hist, ft_atoi(args[0]) - 1);
	}
	return (0);
}

/*
**	ft_builtin_history gere le builtin history dans sa globalité, il check
**	si args est NULL, auquel cas il affiche simplement l'historique, sinon,
**	il appelle ft_exec_history afin que ce dernier gere le comportement
**	du builtin.
*/

int			ft_builtin_history(t_core *g_core, char **args)
{
	int		hsize;
	int		ret;

	ret = 0;
	if (g_core->hist != NULL)
	{
		hsize = 0;
		if ((hsize = ft_get_hsize(g_core->set)) == 0)
		{
			return (ERR_NEW_CMD);
		}
		if (args == NULL || *args == NULL || **args == '\0')
		{
			ft_print_history(g_core->hist, g_core->hist->size);
		}
		else
		{
			ret = ft_exec_history(g_core->set, g_core->hist, args);
		}
	}
	return (ret);
}
