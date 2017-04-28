/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:06:08 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/28 19:12:05 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		init_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void		init_shell(void)
{
	struct sigaction act;

	memset(&act, '\0', sizeof(act));
	act.sa_flags = 0;
	act.sa_handler = &get_sigint;
	sigaction(SIGINT, &act, NULL);
	init_signal();
}
