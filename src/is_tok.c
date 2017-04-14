/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 13:02:54 by alallema          #+#    #+#             */
/*   Updated: 2017/04/14 23:47:08 by nbelouni         ###   ########.fr       */
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
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == ' ')
			return (ESPACE);
	}
	return (0);
}

int		is_dot(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == ';')
			return (DOT);
	}
	return (0);
}

int		is_separator(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
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
	if (i == 0 || s[i - 1] != '\\')
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
