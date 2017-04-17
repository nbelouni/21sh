/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:15:26 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/15 23:45:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		count_prev_char_in_quote(char *s, int *arr, int i, int quote)
{
	int len;

	len = 0;
	while (i - len >= 0 && s[i - len] == '\\' && arr[i - len] == quote)
	{
		len += 1;
	}
	return (len);
}

int		which_quotes(char *s, int len)
{
	int		w_quotes;
	int		i;

	w_quotes = 0;
	i = -1;
	while (++i < len)
	{
		if (is_char(s, i, '"'))
			w_quotes = (w_quotes == NO_QUOTE) ? D_QUOTE : NO_QUOTE;
		if (is_char(s, i, '\''))
			w_quotes = (w_quotes == NO_QUOTE) ? S_QUOTE : NO_QUOTE;
	}
	return (w_quotes);
}

int		supp_char(char *s, int i)
{
	int	j;

	j = i;
	while (j < (int)ft_strlen(s))
	{
		s[j] = s[j + 1];
		j++;
	}
	return (TRUE);
}

void	init_is_in_quote(char *s, int *is_in_quote)
{
	int		iiq_len;
	int		i;
	int		quote;
	int		supp;

	iiq_len = ft_strlen(s);
	i = 0;
	quote = NO_QUOTE;
	while (i < iiq_len)
	{
		supp = FALSE;
		if ((quote != D_QUOTE && is_char(s, i, '\'')) ||
		(quote != S_QUOTE && is_char(s, i, '"')))
		{
			if (quote != D_QUOTE && is_char(s, i, '\''))
				quote = (quote == NO_QUOTE) ? S_QUOTE : NO_QUOTE;
			if (quote != S_QUOTE && is_char(s, i, '"'))
				quote = (quote == NO_QUOTE) ? D_QUOTE : NO_QUOTE;
			supp = supp_char(s, i);
			iiq_len -= 1;
		}
		is_in_quote[i] = quote;
		if (supp == FALSE)
			i += 1;
	}
}

void	supp_quotes(char *s)
{
	int		is_in_quote[ft_strlen(s)];
	int		i;
	int		n_bs;
	int		j;
	int		keep_n_bs;

	init_is_in_quote(s, is_in_quote);
	i = ft_strlen(s);
	j = i;
	while (--i >= 0)
	{
		if ((is_in_quote[--j] == NO_QUOTE && s[i] == '\\') ||
		(is_in_quote[j] == D_QUOTE && (s[i + 1] &&
		(s[i + 1] == '$' || s[i + 1] == '\\' ||
		s[i + 1] == '"') && s[i] == '\\')))
		{
			n_bs = count_prev_char_in_quote(s, is_in_quote, i, is_in_quote[j]);
			keep_n_bs = n_bs / 2;
			n_bs = n_bs / 2 + n_bs % 2;
			while (n_bs > 0 && supp_char(s, i) && (i -= 1) >= 0)
				n_bs -= 1;
			i -= keep_n_bs;
		}
	}
}

int		init_begin_end(char *s, int *begin, int *end)
{
	int		i;

	*begin = find_next_char(s, 0, '$');
	if (*begin < 0 || !ft_isalpha(s[*begin + 1]) ||
	which_quotes(s, *begin) == S_QUOTE)
		return (TRUE);
	*begin += 1;
	i = *begin;
	*end = 0;
	while (s[i + *end] && ft_isalnum(s[i + *end]))
		*end += 1;
	return (FALSE);
}

int		init_new_value(char *var_name, t_core *core, char **new_value)
{
	t_elem	*tmp;

	if (!var_name)
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	if (!(tmp = ft_find_elem(var_name, core->set)))
	{
		if (!(tmp = ft_find_elem(var_name, core->env)))
			tmp = ft_find_elem(var_name, core->exp);
	}
	*new_value = (tmp && tmp->value && tmp->value[0]) ? tmp->value : NULL;
	if (var_name)
		ft_strdel(&var_name);
	return (0);
}

int		replace_env_var(char **s, t_core *core)
{
	char	*new_val;
	char	*new_s;
	int		bg;
	int		end;
	int		tmp_len;

	if (init_begin_end(*s, &bg, &end) == TRUE)
		return (TRUE);
	if (init_new_value(ft_strsub(*s, bg, end), core, &new_val) == ERR_EXIT)
		return (ERR_EXIT);
	if (!(new_s = ft_strnew(ft_strlen(*s) - end + ft_strlen(new_val))))
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	ft_strncpy(new_s, *s, bg - 1);
	if (new_val)
		ft_strncpy(new_s + bg - 1, new_val, ft_strlen(new_val));
	tmp_len = ft_strlen(*s) - (bg + end);
	ft_strncpy(new_s + bg - 1 + ft_strlen(new_val), *s + bg + end, tmp_len);
	new_s[ft_strlen(*s) - (end) + ft_strlen(new_val)] = 0;
	if (*s)
	{
		ft_strdel(s);
		*s = new_s;
	}
	return (FALSE);
}

int		replace_tild(char **s, t_core *core)
{
	t_elem	*tmp;
	char	*new;

	if (!(tmp = ft_find_elem("HOME", core->env)))
		return (0);
	if (!tmp->value)
		return (0);
	if (!(new = ft_strnew(ft_strlen(*s) - 1 + ft_strlen(tmp->value))))
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	ft_strncpy(new, tmp->value, ft_strlen(tmp->value));
	ft_strncpy(new + ft_strlen(tmp->value), *s + 1, ft_strlen(*s) - 1);
	ft_strdel(s);
	*s = new;
	return (0);
}

int		globb(char **s, t_core *core)
{
	int			i;
	int			ret;

	i = 0;
	ret = FALSE;
	if (*s[0] == '~')
	{
		if (replace_tild(s, core) == ERR_EXIT)
			return (ERR_EXIT);
	}
	while (ret == FALSE)
	{
		is_end(*s, &i, '\'');
		if ((ret = replace_env_var(s, core)) == ERR_EXIT)
			return (ERR_EXIT);
		i++;
	}
	supp_quotes(*s);
	return (TRUE);
}

int		edit_cmd(char ***args, t_core *core)
{
	int			i;

	i = -1;
	while ((*args)[++i])
	{
		if (globb(&(*args)[i], core) == ERR_EXIT)
			return (ERR_EXIT);
	}
	return (0);
}
