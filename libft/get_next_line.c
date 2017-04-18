/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 18:14:07 by dogokar           #+#    #+#             */
/*   Updated: 2016/11/22 22:31:00 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			verifline(char *str, int *i)
{
	*i = 0;
	while (str[*i])
	{
		if (str[*i] == '\n')
			return (1);
		*i = *i + 1;
	}
	return (-1);
}

static t_line		*multifd(t_line *node, int fd)
{
	while (node->next != NULL)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	if (node->fd != fd)
	{
		if (!(node->next = (t_line *)malloc(sizeof(t_line))))
			return (NULL);
		node = node->next;
		node->fd = fd;
		node->ret = 0;
		node->tmp = ft_strnew(0);
		node->next = NULL;
	}
	return (node);
}

static t_line		*reader(t_line *sline, char **line)
{
	char			buffer[BUFF_SIZE + 1];
	int				i;

	i = 0;
	if (sline->fd < 0 || read(sline->fd, buffer, 0) < 0 || !line)
		return (NULL);
	(!sline->tmp) ? (sline->tmp = ft_strnew(1)) : (0);
	while ((sline->ret = read(sline->fd, buffer, BUFF_SIZE)))
	{
		buffer[sline->ret] = '\0';
		if ((sline->tmp = ft_strjoin(sline->tmp, buffer)) == NULL)
			return (NULL);
		if (verifline(sline->tmp, &i) > -1)
		{
			*line = ft_strndup(sline->tmp, i);
			return (sline);
		}
	}
	verifline(sline->tmp, &i);
	*line = ft_strndup(sline->tmp, i);
	return (sline);
}

int					get_next_line(int const fd, char **line)
{
	static t_line	*sline;
	t_line			*node;

	node = NULL;
	if (!sline)
	{
		if (!(sline = (t_line *)malloc(sizeof(t_line))))
			return (-1);
		sline->fd = fd;
		sline->tmp = ft_strnew(0);
		sline->next = NULL;
		sline->ret = 0;
	}
	node = sline;
	node = multifd(node, fd);
	if (!(node = reader(node, line)))
		return (-1);
	if (((node->tmp = ft_strchr(node->tmp, '\n')) != NULL) && node->tmp++)
		return (1);
	else if (node->tmp == NULL && node->ret == 0 && *line[0] == '\0')
		return (0);
	return (1);
}
