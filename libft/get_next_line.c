/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 16:53:21 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/18 15:29:54 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_sub_reloaded(t_str *s_str, char **line, int const fd)
{
	char			*tmp;

	tmp = NULL;
	if (s_str->fd != fd)
	{
		s_str->i = 0;
		s_str->j = 0;
		s_str->fd = fd;
	}
	while (s_str->s[s_str->i])
	{
		if (s_str->s[s_str->i] == '\n')
		{
			tmp = *line;
			*line = ft_strsub(s_str->s, s_str->j, (s_str->i - s_str->j));
			ft_strdel(&tmp);
			s_str->i++;
			s_str->j = s_str->i;
			return (1);
		}
		s_str->i++;
	}
	return (0);
}

static int	exec_get_next_line(t_str *s_str, char **s, int const fd, char *buf)
{
	char			*tmp;

	tmp = NULL;
	while ((s_str->read = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[s_str->read] = '\0';
		s_str->s = ft_free_and_join(s_str->s, buf);
	}
	if (s_str->read == -1)
		return (-1);
	if (ft_sub_reloaded(s_str, s, fd) == 1)
		return (1);
	tmp = *s;
	*s = ft_strsub(s_str->s, s_str->j, (s_str->i - s_str->j));
	ft_strdel(&tmp);
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	static t_str	s_str;

	ret = 0;
	if (BUFF_SIZE <= 0 || !line || fd < 0)
		return (-1);
	if (!s_str.s)
		s_str.fd = fd;
	if (!s_str.s || s_str.fd != fd)
	{
		if ((s_str.s = (char *)malloc(sizeof(s_str.s))))
			s_str.s[0] = '\0';
		else
			return (-2);
	}
	if ((ret = exec_get_next_line(&s_str, line, fd, buf)) < 0)
		free(s_str.s);
	return (ret);
}
