/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:04:03 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/26 18:04:20 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "io.h"
#include "job.h"

static int	return_or_exit(char *error, int dofork)
{
	if (dofork)
		exit(ft_print_error("21sh", error, ERR_EXIT));
	return (1);
}

static int	redir_open(t_io *io, int dofork)
{
	if (io->flag & CLOSE && access(io->str, X_OK) == -1)
		io->dup_src = open(io->str, io->mode, DEF_FILE);
	if (access(io->str, 0) == 0 && access(io->str, R_OK | W_OK) == -1)
	{
		return (ft_print_error("21sh", ERR_NO_ACCESS,
			return_or_exit(ERR_NO_ACCESS, dofork)));
	}
	if (io->dup_src < 0)
	{
		return (ft_print_error("21sh", ERR_NO_FILE,
			return_or_exit(ERR_NO_FILE, dofork)));
	}
	return (0);
}

int			apply_redir(t_io *io, int dofork)
{
	int		pipefd[2];
	int		ret;

	if (io->flag & OPEN)
	{
		if ((ret = redir_open(io, dofork)))
			return (ret);
	}
	if (io->flag & WRITE && pipe(pipefd) != -1)
	{
		io->dup_src = pipefd[0];
		write(pipefd[1], io->str, ft_strlen(io->str));
		close(pipefd[1]);
	}
	if (io->flag & DUP)
	{
		if (dup2(io->dup_src, io->dup_target) == -1 && dofork)
			return (ft_print_error("21sh", ERR_BADF,
				return_or_exit(ERR_BADF, dofork)));
	}
	if (io->flag & CLOSE && io->flag ^ WRITE)
		close(io->dup_src);
	return (0);
}
