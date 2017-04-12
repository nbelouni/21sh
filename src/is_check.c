/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:26:10 by alallema          #+#    #+#             */
/*   Updated: 2017/04/12 19:21:44 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		find_bracket_end(char *s, int i)
{
	int		len;

	len = 0;
	if (i == 0 || s[i - 1] != '\\')
	{
		while (s[i + len])
		{
			if (i > 0 && s[i + len] && s[i + len] == ' '
				&& is_dot(s, i + len) == 1)
				break ;
			len++;
		}
		if (!s[i + len])
			return (-1);
		return (len);
	}
	return (0);
}

int		is_redir(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (!ft_strncmp(s + i, "<<", 2))
			return (DL_DIR);
		if (!ft_strncmp(s + i, ">>", 2))
			return (DR_DIR);
		if (!ft_strncmp(s + i, "<>", 2))
			return (LR_DIR);
		if (s[i] == '>')
			return (SR_DIR);
		if (s[i] == '<')
			return (SL_DIR);
	}
	return (0);
}

int		is_agreg(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (!ft_strncmp(s + i, "<&", 2))
			return (DIR_L_AMP);
		if (!ft_strncmp(s + i, ">&", 2))
			return (DIR_R_AMP);
	}
	return (0);
}

int		is_or_and(char *s, int i)
{
	if (i == 0 || s[i - 1] != '\\')
	{
		if (s[i] == '|')
			return (PIPE);
	}
	return (0);
}

int		is_bracket(char *s, int i)
{
	(void)s;
	(void)i;
	return (0);
}
