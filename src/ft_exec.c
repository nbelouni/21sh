/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alallema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:08:28 by alallema          #+#    #+#             */
/*   Updated: 2017/04/22 18:16:42 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** decoupe la path pour effectue l'execution du binaire dans chaque dossier
*/

extern t_core	*g_core;

static char		*ft_cut_path(char **s, char *av)
{
	char		*s1;
	char		*s2;
	char		*tmp;
	int			i;

	i = 0;
	s1 = *s;
	while (s1[i] && s1[i] != ':')
		i++;
	s2 = ft_memalloc(sizeof(char) * (i + 2 + ft_strlen(av)));
	ft_strncpy(s2, s1, i);
	ft_strncpy(s2 + i, "/", 1);
	ft_strncpy(s2 + i + 1, av, ft_strlen(av));
	if (s1[i] && s1[i] == ':')
		i++;
	tmp = ft_strdup(s1 + i);
	s1 = NULL;
	ft_strdel(s);
	*s = tmp;
	return (s2);
}

/*
** fonction d'execution des commandes via execve
** lstat verifie l'authorisation d'execution
*/

void			not_binary(char *s, char *s2, char **av, char **envp)
{
	struct stat	st;

	if (lstat(av[0], &st) == 0 && st.st_mode & S_IXUSR && access(av[0], X_OK) == 0)
		execve(av[0], av, envp);
	if (s2 && lstat(s2, &st) == 0 && st.st_mode & S_IXUSR && access(s2, X_OK) == 0)
		execve(s2, av, envp);
	if (!s || ft_strcmp(s, "") == 0)
	{
		(s) ? free(s) : 0 ;
		(s2) ? free(s2) : 0 ;
		(envp) ? ft_tabdel(envp) : 0;
		if (lstat(av[0], &st) == 0 && st.st_mode & S_IXUSR)
			ft_putstr_fd("21sh: exec format error: ", 2);
		else if (lstat(av[0], &st) == 0)
			ft_putstr_fd("21sh: permission denied: ", 2);
		else if (!s)
			ft_putstr_fd("21sh: no such file or directory: ", 2);
		else
			ft_putstr_fd("21sh: command not found: ", 2);
		ft_putendl_fd(av[0], 2);
		exit(1);
	}
}

/*
** recuperer l'env pour execve
** remplace le path pour l'envoie a execve
*/

void			ft_exec(char **av)
{
	char		*s;
	char		*s2;
	char		**envp;
	t_elem		*tmp;

	s2 = NULL;
	close_termios();
	envp = ft_env_to_tab(g_core->env);
	if (!(tmp = ft_find_elem("PATH", g_core->env)) || !tmp->value)
		s = ft_strdup("");
	else
		s = ft_strdup(tmp->value);
	if (av && av[0] && av[0][0] && ((av[0][0] == '.' && av[0][1] == '/') ||
			(av[0][0] == '/')))
		not_binary(NULL, NULL, av, envp);
	while (true)
	{
		s2 = ft_cut_path(&s, av[0]);
		not_binary(s, s2, av, envp);
		(s2) ? ft_strdel(&s2) : 0;
		if (!s)
			break ;
	}
	ft_putstr_fd("21sh: command not found: ", 2);
	(s) ? free(s) : 0;
	(s2) ? free(s2) : 0;
	(envp) ? ft_tabdel(envp) : 0;
	ft_putendl_fd(av[0], 2);
	exit(37);
}

/*
** edit_cmd remplace la commande avec la completion
** sert a retourner si la cmd c'est un builtin
*/

int				ft_check_exec(char ***cmd)
{
	int			ret;
	char		*s;

	s = NULL;
	ret = TRUE;
	if (edit_cmd(cmd, g_core) == ERR_EXIT)
		return (ERR_EXIT);
	if (**cmd && (ret = parse_builtins(g_core, *cmd[0], *cmd + 1)) == 1)
		ft_exec(*cmd);
	else
	{
		ft_setenv(g_core->set, "RET", (s = ft_itoa(ret)));
		free(s);
	}
	return (ret);
}
