/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:12:21 by maissa-b          #+#    #+#             */
/*   Updated: 2017/05/03 20:39:48 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H

# include "ft_21sh.h"

/*
**	find_quote_end.c
**	trouve le prochain caractere identique a c si s[i] == c
*/
int		is_end(char *s, int *i, char c);

/*
**	find_quote_end.c
**	trouve le caractere precedant identique a c si s[i] == c
*/
int		is_begin(char *s, int *i, char c);

/*
**	renvoie NO_QUOTES si s[len] n'est pas a l'interieur de quotes,
**	sinon renvoie le type de quotes (e_flag dans lexer_parser.h)
*/
int		which_quotes(char *s, int len);

/*
**	remplace les variables d'environnement,
**	supprime les quotes,
**	supprime les backslashs si necessaire
*/
int		edit_cmd(char ***args, t_core *core);

int		count_prev_char_in_quote(char *s, int *arr, int i, int quote);
int		which_quotes(char *s, int len);
int		supp_char(char *s, int i);
void	init_is_in_quote(char *s, int *is_in_quote);
void	supp_quotes(char *s);
int		init_begin_end(char *s, int *begin, int *end);

#endif
