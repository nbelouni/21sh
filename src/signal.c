/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:10:58 by alallema          #+#    #+#             */
/*   Updated: 2017/04/22 20:17:04 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_core	*g_core;

t_bool		get_win(void)
{
	struct winsize	windows;

	if (ioctl(0, TIOCGWINSZ, &windows) < 0)
		return (FALSE);
	g_curs.win_col = windows.ws_col;
	g_curs.win_row = windows.ws_row;
	return (TRUE);
}

void		get_sigwinch(int sig)
{
//	char	*tmp;
//	int		i;
//	signal(SIGWINCH, SIG_IGN);
//	tmp = ft_strdup(g_core->buf->line);
//	vb_del(g_core->buf, CTRL_K);
//	clean_pos_curs();
//	signal(SIGWINCH, SIG_DFL);
//	kill(pid, 28);
	if (sig == SIGWINCH)
		get_win();
//	i = -1;
//	while (tmp[++i])
//		vb_insert(g_core->buf, tmp + i);
//	ft_strdel(&tmp);
//	sleep(10);
//	t_puts("cl");
	//print_post_curs(g_core->buf);
//	m_right(g_core->buf->size);
	return ;
}

void		get_sigint(int sig)
{
	int status;
	int pid;

	pid = waitpid(-1, &status, WUNTRACED);
	if (sig == SIGINT)
	{
		m_right(calc_len(g_core->buf, END));
		g_core->buf->size = 0;
		ft_bzero(g_core->buf->line, BUFF_SIZE);
		clean_pos_curs();
		if (pid == -1)
			ft_putstr_fd("\n21sh.$ ", 1);
	}
	return ;
}
