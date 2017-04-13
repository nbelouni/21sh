/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:31:30 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/13 15:37:27 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H

# include "21sh.h"

/*
**	find_quote_end.c
**	trouve le prochain caractere identique a c si s[i] == c
*/
int						is_end(char *s, int *i, char c);

/*
**	find_quote_end.c
**	trouve le caractere precedant identique a c si s[i] == c
*/
int						is_begin(char *s, int *i, char c);

/*
**	renvoie NO_QUOTES si s[len] n'est pas a l'interieur de quotes,
**	sinon renvoie le type de quotes (e_flag dans lexer_parser.h)
*/
int						which_quotes(char *s, int len);

#endif
