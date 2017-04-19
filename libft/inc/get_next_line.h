/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 18:15:17 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/18 11:50:00 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"
# include <fcntl.h>

typedef struct	s_str
{
	int			i;
	int			j;
	int			read;
	int			fd;
	char		*s;
}				t_str;

int				get_next_line(int const fd, char **line);

#endif
