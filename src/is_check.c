/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:06:04 by nbelouni          #+#    #+#             */
/*   Updated: 2017/05/03 18:12:33 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		is_redir(char *s, int i)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (i + 1 < (int)ft_strlen(s))
		{
			if (!ft_strncmp(s + i, "<<", 2))
				return (DL_DIR);
			if (!ft_strncmp(s + i, ">>", 2))
				return (DR_DIR);
			if (!ft_strncmp(s + i, "<>", 2))
				return (LR_DIR);
		}
		if (s[i] == '>')
			return (SR_DIR);
		if (s[i] == '<')
			return (SL_DIR);
	}
	return (0);
}

int		is_agreg(char *s, int i)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (i + 1 < (int)ft_strlen(s))
		{
			if (!ft_strncmp(s + i, "<&", 2))
				return (DIR_L_AMP);
			if (!ft_strncmp(s + i, ">&", 2))
				return (DIR_R_AMP);
		}
	}
	return (0);
}

int		is_or_and(char *s, int i)
{
	if (i == 0 || count_prev_char(s, i - 1, '\\') % 2 == 0)
	{
		if (s[i] == '&' || s[i] == '|')
		{
			if (i + 1 < (int)ft_strlen(s))
			{
				if (!ft_strncmp(s + i, "&&", 2))
					return (AND);
				if (!ft_strncmp(s + i, "||", 2))
					return (OR);
			}
			if (s[i] == '|')
				return (PIPE);
		}
	}
	return (0);
}
