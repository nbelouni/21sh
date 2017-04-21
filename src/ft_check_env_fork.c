/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 19:55:36 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/21 19:55:38 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int					ft_env_binary(char **args)
{
	int	*opt;

	opt = NULL;
	if ((opt = ft_opt_parse(ENV_OPT, args + 1, 0, 1)) == NULL)
		return (0);
	if (opt[0] < 0 || !args[opt[0] + 1])
	{
		(opt) ? free(opt) : 0;
		return (0);
	}
	(opt) ? free(opt) : 0;
	return (1);
}
