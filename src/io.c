/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:02:14 by alallema          #+#    #+#             */
/*   Updated: 2017/04/27 19:32:38 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "io.h"

t_io	*new_io(int flag, int mode)
{
	t_io	*io;

	if (!(io = ft_memalloc(sizeof(t_io))))
		return (NULL);
	ft_bzero(io, sizeof(t_io));
	io->flag = flag;
	io->mode = mode;
	io->tab_fd[0] = -1;
	io->tab_fd[1] = -1;
	return (io);
}
