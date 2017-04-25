/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:10:58 by alallema          #+#    #+#             */
/*   Updated: 2017/04/25 15:47:40 by nbelouni         ###   ########.fr       */
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
//	int		pid;
	int		len;

	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len();
	PUT2("len : ");E(len);X('\n');
//	PUT2("col : ");E(g_curs.col);X('\n');
//	PUT2("row : ");E(g_curs.row);X('\n');
//	PUT2("win_col : ");E(g_curs.win_col);X('\n');
//	PUT2("win_row : ");E(g_curs.win_row);X('\n');
	if (sig == SIGWINCH)
		get_win();
//	tmp ////= ft_strdup(g_core->buf->line);
	
//	m_right(g_core->buf->size - len);
//	vb_del(g_core->buf, CTRL_K);
//	PUT2("col : ");E(g_curs.col);X('\n');
//	PUT2("row : ");E(g_curs.row);X('\n');
//	PUT2("win_col : ");E(g_curs.win_col);X('\n');
//	PUT2("win_row : ");E(g_curs.win_row);X('\n');
//	int status;
//	pid = waitpid(-1, &status, WUNTRACED);
//	kill(pid, 28);
//	signal(SIGWINCH, SIG_DFL);
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
		ft_strdel(&(g_core->buf->final_line));
		set_prompt(PROMPT1, ft_strlen(PROMPT1));
		clean_pos_curs();
		if (pid == -1)
		{
			ft_putchar('\n');
			ft_putstr_fd(get_prompt_str(), 1);
		}
	}
	return ;
}
