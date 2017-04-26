/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:05:53 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:10:12 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		cut_space(char *s, int i)
{
	while (is_space(s, i) == ESPACE)
		i++;
	return (i);
}

int		is_space(char *s, int i)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (s[i] == ' ')
			return (ESPACE);
	}
	return (0);
}

int		is_dot(char *s, int i)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (s[i] == ';')
			return (DOT);
	}
	return (0);
}

int		is_separator(char *s, int i)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (s[i] == '|' || s[i] == ';')
			return (1);
		if (i + 1 < (int)ft_strlen(s) &&
		(!ft_strncmp(s + i, "||", 2) || !ft_strncmp(s + i, "&&", 2)))
			return (2);
	}
	return (0);
}

int		is_redirection(char *s, int i)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '&')
			return (1);
		if (i + 1 < (int)ft_strlen(s) &&
		(!ft_strncmp(s + i, "<<", 2) || !ft_strncmp(s + i, ">>", 2)
		|| !ft_strncmp(s + i, "&>", 2)))
			return (2);
	}
	return (0);
}
