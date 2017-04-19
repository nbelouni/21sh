/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:10:58 by alallema          #+#    #+#             */
/*   Updated: 2017/04/19 19:02:15 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_core	*g_core;
extern t_list	*g_job_list;
extern t_job	*last_job;

t_bool		get_win(void)
{
	struct winsize	windows;

	if (ioctl(0, TIOCGWINSZ, &windows) < 0)
		return (FALSE);
	g_curs.win_col = windows.ws_col;
	g_curs.win_row = windows.ws_row;
	return (TRUE);
}

void		get_sigint(int sig)
{
	int status;
	int pid;
	pid = waitpid(-1, &status, WUNTRACED);
	if (sig == SIGINT)
	{
		g_core->buf->size = 0;
		ft_bzero(g_core->buf->line, BUFF_SIZE);
		clean_pos_curs();
		if (pid == -1)
		ft_putstr_fd("\n21sh.$ ", 1);
	}
	return ;
}
