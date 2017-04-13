/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:02:14 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/13 15:36:40 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "io.h"

t_io	*new_io(int flag, int mode)
{
	t_io	*io;

	if (!(io = ft_memalloc(sizeof(t_io))))
		return (NULL);
	bzero(io, sizeof(t_io));
	io->flag = flag;
	io->mode = mode;
	io->tab_fd[0] = -1;
	io->tab_fd[1] = -1;
	io->tab_fd[2] = -1;
	return (io);
}
