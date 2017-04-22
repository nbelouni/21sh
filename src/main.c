/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissa-b <maissa-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:16:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/04/20 18:31:24 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_list	*g_job_list = NULL;
t_core	*g_core = NULL;

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
	{"loc", &ft_builtin_locale},
	{NULL, NULL}
};

/*
**	  init_core initialisation des liste d'env
*/

int			parse_builtins(t_core *core, char *cmd, char **cmd_args)
{
	int	i;

	i = -1;
	while (g_builtin_array[++i].cmd)
	{
		if (ft_strcmp(g_builtin_array[i].cmd, cmd) == 0)
		{
			return (g_builtin_array[i].func(core, cmd_args));
		}
	}
	return (1);
}

/*
**   si l'entree est different du terminal va lire ligne par ligne GNL
*/

static int	launch_execution(int ret, t_buf *buf, t_token *list)
{
	t_list	*job_list_bis;
	t_tree	*ast;

	job_list_bis = NULL;
	ast = NULL;
	if ((ret = ft_cmd_to_history(g_core->hist, buf->final_line)) == ERR_EXIT)
	{
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	}
	if ((ret = ft_check_history_var(g_core)) == ERR_EXIT)
	{
		return (ft_print_error("21sh: ", ERR_MALLOC, ERR_EXIT));
	}
	ft_push_ast(list, &ast);
	export_job(ast, &job_list_bis);
	list_iter(job_list_bis, (void *)launch_job);
	delete_list(&job_list_bis, NULL);
	free_ast(ast);
	return (ret);
}

static int	pre_core(t_buf *buf, t_completion *completion, char **envp)
{
	struct termios termio;

	tcgetattr(0, &termio);
	if (ft_creat_core(envp) == ERR_EXIT)
		return (ERR_EXIT);
	if (!(buf = init_buf()))
		return (ft_print_error("21sh", ERR_MALLOC, ERR_EXIT));
	if (init_completion(completion, g_core) == ERR_EXIT)
		return (-1);
	if (!isatty(0))
		return (ft_print_error("21sh", " : Input not from a tty", ERR_NEW_CMD));
	set_prompt(PROMPT1, ft_strlen(PROMPT1));
	init_shell();
	g_core->buf = buf;
	init_curs();
	return (0);
}

static int	exec_core(int ret, t_completion *completion, t_buf *buf)
{
	int				ret_subs;
	t_token			*list;

	list = NULL;
	ret_subs = 0;
	if (is_line_ended(g_core->buf) < 0)
		return (-1);
	ret_subs = bang_substitution(&(g_core->buf->final_line), g_core);
	ret = parse_buf(&list, g_core->buf->final_line, completion, g_core->hist);
	if (ret > 0 && list && ret_subs == 0)
		ret = launch_execution(ret, buf, list);
	else if (ret_subs == 2)
		ft_putendl(buf->final_line);
	if (ret != ERR_NEW_PROMPT && g_core->buf->final_line)
		ft_strdel(&(g_core->buf->final_line));
	else
		complete_final_line(g_core->buf, list);
	if (list)
		ft_tokendestroy(&list);
	ft_bzero(g_core->buf->line, BUFF_SIZE);
	g_core->buf->size = 0;
	clean_pos_curs();
	if (init_completion(completion, g_core) == ERR_EXIT)
		return (-1);
	return (ret);
}

int			main(int argc, char **argv, char **envp)
{
	t_completion	cplt;
	t_buf			*buf;
	int				ret;
	int				read;

	(void)argc;
	(void)argv;
	buf = NULL;
	ft_memset(&cplt, 0, sizeof(t_completion) * 4);
	ret = pre_core(buf, &cplt, envp);
	while ((read = read_line(g_core->buf, &cplt, g_core->hist)) != ERR_NEW_CMD)
	{
		close_termios();
		if (read != TAB)
		{
			ret = exec_core(ret, &cplt, buf);
		}
		if (read == END_EOT)
			break ;
	}
	close_termios();
	free_buf(g_core->buf);
	return (0);
}
