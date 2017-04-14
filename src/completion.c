/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:10:02 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/14 23:06:27 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	print_slist(t_slist *lst, int n, char c)
{
	t_slist		*tmp;
	int			word_per_line;
	int			max_len;
	int			i;

	close_termios();
	tmp = lst;
	max_len = max_len_sort_lst(lst, n) + 3;
	word_per_line = g_curs.win_col / max_len;
	ft_putchar_fd('\n', 1);
	while (n-- && tmp)
	{
		write(1, &c, 1);
		ft_putstr_fd(tmp->s, 1);
		i = -1;
		while ((int)ft_strlen(tmp->s) + ++i < max_len)
			ft_putchar_fd(' ', 1);
		word_per_line--;
		if (word_per_line == 0)
			word_per_line = g_curs.win_col / max_len + ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	ft_putchar_fd('\n', 1);
}

int		replace_cplt(t_buf *buf, char *ref, int bg)
{
	int		len;
	int		i;

	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - bg;
	while (len-- > 0)
		vb_del(buf, DEL);
	len = ft_strlen(ref);
	i = -1;
	while (++i < len)
		vb_insert(buf, &(ref[i]));
	buf->size = ft_strlen(buf->line);
	return (0);
}

int		fill_file(t_buf *buf, t_slist **lst, int *bg)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				n_lst;
	int				len;

	*lst = NULL;
	n_lst = 0;
	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - *bg;
	if (buf->line[*bg] == '/')
	{
		if (open_abs_path(buf->line, &dirp, bg) != TRUE)
			return (ERR_EXIT);
	}
	else if (open_rel_path(buf->line, &dirp, bg) != TRUE)
		return (ERR_EXIT);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (insert_in_list(lst, dp->d_name) == ERR_EXIT)
			return (ERR_EXIT);
		n_lst++;
	}
	closedir(dirp);
	return (n_lst);
}

int		replace_or_print(t_buf *buf, t_slist *ref, int begin, char c)
{
	int			n_lst;
	int			len;
	char		*s;
	t_slist		*lst;

	s = buf->line;
	lst = NULL;
	len = (g_curs.win_col * g_curs.row + g_curs.col) - get_prompt_len() - begin;
	if (!s[0])
	{
		lst = ref;
		n_lst = count_sort_lst(ref);
	}
	else
		n_lst = find_cplt(s + begin, ref, &lst, len);
	if (n_lst == 1)
		replace_cplt(buf, lst->s, begin);
	else if (n_lst > 1)
		print_slist(lst, n_lst, c);
	return (n_lst > 1 ? TAB : 0);
}

int		complete_line(t_buf *buf, t_completion *cplt, char x)
{
	t_slist		*ref;
	int			begin;
	int			ret;

	if (x != TAB || buf->size >= BUF_SIZE)
		return (0);
	begin = find_word_begin(buf->line);
	if (is_char(buf->line, begin, '$'))
		return (replace_or_print(buf, cplt->variable, begin + 1, '$'));
	if (is_char(buf->line, begin, '~'))
		return (replace_or_print(buf, cplt->username, begin + 1, '~'));
	if (is_char(buf->line, begin, '@'))
		return (replace_or_print(buf, cplt->hostname, begin + 1, '@'));
	if (is_cmd(buf->line, begin - 1))
		return (replace_or_print(buf, cplt->command, begin, 0));
	if (is_arg(buf->line, begin - 1))
	{
		if ((ret = fill_file(buf, &ref, &begin)) < 0)
			return (ret);
		ret = replace_or_print(buf, ref, begin, 0);
		if (ref)
			destroy_sort_list(&ref);
		return (ret);
	}
	return (0);
}
