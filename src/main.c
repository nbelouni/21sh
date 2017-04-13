/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/13 16:37:23 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	launch_job(t_job *j);
void	export_job(t_tree *root, t_list **job_list);
void	printJobList(t_list *job_list);

t_list	*job_list = NULL;
t_job	*last_job = NULL;

static t_builtin_array g_builtin_array[] =
{
	{"cd", &ft_builtin_cd},
	{"env", &ft_builtin_env},
	{"setenv", &ft_builtin_setenv},
	{"unsetenv", &ft_builtin_unsetenv},
	{"exit", &ft_builtin_exit},
	{"echo", &ft_builtin_echo},
	{"history", &ft_builtin_history},
	{"unset", &ft_builtin_unset},
	{"export", &ft_builtin_export},
	{NULL, NULL}
};

int		parse_builtins(t_core *core, char *cmd, char **cmd_args)
{
	int	i;

	i = -1;
	while (g_builtin_array[++i].cmd)
	{
		if (ft_strcmp(g_builtin_array[i].cmd, cmd) == 0)
			return (g_builtin_array[i].func(core, cmd_args));
	}
	return (1);
}

/*
**	  init_core initialisation des liste d'env
*/

t_core 		*ft_creat_core(char **envp)
{
	t_core *core;

	core = ft_init_core();
	core->set = ft_init_lstset();
	core->exp = ft_init_list();
	if (envp != NULL && envp[0] != NULL)
		core->env = ft_env_to_list(envp, core->env);
	else
		core->env = ft_default_env();
	ft_histopt_r(&(core->hist), core->set, NULL);
	return (core);
}

/*
**   si l'entree est different du terminal va lire ligne par ligne GNL
*/

int 	read_ext(t_buf *buf, t_completion *comp, t_core *core, t_token *list)
{
	int i;
	char *line = NULL;

	i = 0;
	if (buf->istty == 1)
	{
		while (get_next_line(0, &line) > 0)
		{
			buf->final_line = line;
			PUT2(buf->final_line);
			parse_buf(&list, buf->final_line, comp, core->hist);
			PUT2("\n line "); E(i);
			ft_print_token_list(&list);
			++i;
		}
		return (0);
	}
	return (1);
}

int 	main(int argc, char **argv, char **envp)
{
	(void)argc;
  	(void)argv;
	t_completion	completion = {NULL, NULL, NULL, NULL};
	t_buf	*buf;
	t_token	*list;
	int		ret;
	int		ret_read;
	t_tree	*ast;
	t_list	*job_list_bis = NULL;
	struct termios termio;

	tcgetattr(0, &termio);
	ast = NULL;
	list = NULL;
	core = ft_creat_core(envp);
	if (!(buf = init_buf()))
		return (ft_print_error("21sh", ERR_MALLOC, ERR_EXIT));
	if (init_completion(&completion, core) == ERR_EXIT)
		return (-1);
	if (!isatty(0))
		buf->istty = 1;
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_shell();
	core->buf = buf;
	if (read_ext(core->buf, &completion, core, list) == 1)
	{
		init_curs();
		while ((ret_read = read_line(core->buf, &completion, core->hist)) != ERR_EXIT)
		{
			close_termios();
			job_list_bis = NULL;
			if (ret_read != TAB)
			{
				if (is_line_ended(core->buf) < 0)
					return (-1);
				bang_substitution(&(core->buf->final_line), core);
				ret = parse_buf(&list, core->buf->final_line, &completion, core->hist);
				if (ret > 0 && list)
				{
					if ((ret = ft_cmd_to_history(core->hist, buf->final_line)) == ERR_EXIT)
						return (ERR_EXIT);
/*
 *					enleve les quotes et les backslash -> va changer de place
 *					edit_cmd(list, env);
 */	
					ft_push_ast(list, &ast);
//					regexp_in_tree(ast, core);
//					print_debug_ast(ast);
//					test_func(ast);
					export_job(ast, &job_list_bis);
//					printJobList(job_list_bis);
					list_iter(job_list_bis, (void *)launch_job);
					delete_list(&job_list_bis, NULL);
					free_ast(ast);
//					free(ast);
/*
**				. remplace $var
**				. ajoute arguments si regex
**				. supprime '\'', '"' , '`' et '\\'
**
**				. sera remplacee quqnd je saurais ou la mettre
**
*/
					if ((ret = ft_check_history_var(core->set, core->hist)) == ERR_EXIT)
						return (ERR_EXIT);
				}
//				ft_print_token_list(&list);
				if (ret != ERR_NEW_PROMPT && core->buf->final_line)
					ft_strdel(&(core->buf->final_line));
				else
					complete_final_line(core->buf, list);
				if (list)
					ft_tokendestroy(&list); //clean la list a mettre a la fin
				ft_bzero(core->buf->line, BUFF_SIZE);
				core->buf->size = 0;
				clean_pos_curs();
				if (init_completion(&completion, core) == ERR_EXIT)
					return (-1);
			}
			if (ret_read == END_EOT)
				break ;
		}
		close_termios();
	}
	free_buf(core->buf);
	return (0);
}
