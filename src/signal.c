/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:10:58 by alallema          #+#    #+#             */
/*   Updated: 2017/04/26 13:17:39 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

extern t_core	*g_core;

t_bool		get_win(void)
{
	struct winsize	windows;
	int				len;

	len = get_curs_add(-(get_prompt_len()));
	if (ioctl(0, TIOCGWINSZ, &windows) < 0)
		return (FALSE);
	if ((g_curs.win_col * g_curs.row) + g_curs.col >= (int)get_prompt_len())
	{
		t_puts("cl", 1);
		ft_putstr_fd(get_prompt_str(), 1);
	}
	g_curs.win_col = windows.ws_col;
	g_curs.win_row = windows.ws_row;
	clean_pos_curs();
	print_post_curs(g_core->buf);
	m_right(len);
	return (TRUE);
}

void		get_sigwinch(int sig)
{
	if (sig == SIGWINCH)
		get_win();
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
		ft_strdel(&(g_core->buf->final_line));
		set_prompt(PROMPT1, ft_strlen(PROMPT1));
		clean_pos_curs();
		ft_putchar('\n');
		if (pid == -1)
		{
			ft_putstr_fd(get_prompt_str(), 1);
		}
	}
	return ;
}
