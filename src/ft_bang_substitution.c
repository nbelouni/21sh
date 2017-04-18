/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bang_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 18:15:57 by maissa-b          #+#    #+#             */
/*   Updated: 2017/04/13 20:18:53 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		print_sub(t_lst *hist, char **s, int *i)
{
	int		ret;
	char	*tmp;
	char	*tmp2;

	ret = 0;
	tmp = NULL;
	tmp2 = NULL;
	if (!(tmp = ft_strsub(*s, 0, ft_strlen(*s) - \
			ft_strlen(ft_strstr(*s, ":p")))))
	{
		return (ERR_EXIT);
	}
	ret = switch_bang(hist, &tmp, i);
	tmp2 = *s;
	*s = ft_strreplace(tmp2, *s, tmp);
	ft_strdel(&tmp2);
	ft_strdel(&tmp);
	return ((ret < 0) ? ret : 2);
}

int		switch_bang(t_lst *hist, char **s, int *i)
{
	int		ret;
	char	*n;

	if (!((*s)[*i]))
		return (ft_print_error("21sh: event not found: ", *s, -1));
	n = NULL;
	ret = 0;
	if (((*s)[*i]) == '!')
		ret = dbang_sub(hist, s);
	else if (((*s)[*i]) == '$')
		ret = bang_doll_sub(hist->tail->name, s);
	else if (((*s)[*i]) == '*')
		ret = bang_wildcard_sub(hist->tail->name, s);
	else if (((*s)[*i]) == '#')
		ret = bang_diese_sub(s, *i);
	else if ((n = find_number(&((*s)[*i]))))
		ret = bang_number_sub(hist, s, n);
	else if (((*s)[*i]) != '?' && (n = find_replace_cmd(*s + *i)))
		ret = bang_start_occur_sub(hist, s, n);
	else if (((*s)[*i]) == '?' && (n = find_replace_cmd((*s + *i) + 1)))
		ret = bang_contain_occur_sub(hist, s, n);
	(n) ? ft_strdel(&n) : 0;
	return (ret);
}

int		bang_substitution(char **s, t_core *core)
{
	int		i;
	int		squote;
	int		ret;

	i = -1;
	squote = 0;
	ret = 0;
	while ((*s)[++i])
	{
		if (is_char(*s, i, '\''))
			squote++;
		if (squote % 2 == 0)
		{
			if (is_char(*s, i, '!'))
			{
				++i;
				if (!ft_strstr(*s, ":p"))
					ret = switch_bang(core->hist, s, &i);
				else
					ret = print_sub(core->hist, s, &i);
			}
			else if (is_char(*s, i, '^'))
				ret = ft_exec_quick_sub(core->hist->tail, s, &i);
			if (ret < 0)
				break ;
		}
	}
	return (ret);
}
