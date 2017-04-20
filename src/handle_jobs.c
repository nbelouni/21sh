/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:15:02 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/20 20:57:07 by maissa-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "io.h"
#include "job.h"
#include <errno.h>

extern	t_list	*g_job_list;
extern	t_core	*g_core;
/*
** Store the status of the process pid that was returned by waitpid.
** Return 0 if all went well, nonzero otherwise.
*/

t_process_p		get_process_by_pid(pid_t pid)
{
	t_list		*ptr_job;
	t_list		*ptr_process;
	t_job		*j;
	t_process_p	p;

	ptr_job = g_job_list;
	while (ptr_job)
	{
		j = ptr_job->content;
		ptr_process = j->wait_process_list;
		while (ptr_process)
		{
			p = ptr_process->content;
			if (p->pid == pid)
				return (p);
			ptr_process = ptr_process->next;
		}
		ptr_job = ptr_job->next;
	}
	return (NULL);
}

t_job	*get_job_from_pid(pid_t pid)
{
	t_list		*ptr_job;
	t_list		*ptr_process;
	t_job		*j;
	t_process_p	p;

	ptr_job = g_job_list;
	while (ptr_job)
	{
		j = ptr_job->content;
		ptr_process = j->wait_process_list;
		while (ptr_process)
		{
			p = ptr_process->content;
			if (p->pid == pid)
				return (j);
			ptr_process = ptr_process->next;
		}
		ptr_job = ptr_job->next;
	}
	return (NULL);
}

int		mark_process_status(pid_t pid, int status, int *last)
{
	t_process_p	p;

	if (pid > 0)
	{
		if ((p = get_process_by_pid(pid)))
		{
			p->status = status;
			get_job_from_pid(pid)->status = status;
			if (WIFSTOPPED(status))
				p->stopped = 1;
			else
			{
				p->completed = 1;
				*last = WEXITSTATUS(status);
/*				if (WIFSIGNALED(status))
				{
					ft_putstr_fd("21sh: Terminated by signal ", 2);
					ft_putnbr_fd(WTERMSIG(status), 2);
					ft_putchar_fd('\n', 2);
				}
*/			}
			return (0);
		}
		else
			return (-1);
	}
	else if (pid == 0 || errno == ECHILD)
		return (-1);
	else
		return (-1);
}

/*
** Check for processes that have status information available,
** blocking until all processes in the given job have reported.
*/

int		job_is_complete(t_job *j)
{
	t_process *p;
	t_list		*ptr;

	ptr = j->wait_process_list;
	while (ptr)
	{
		p = ptr->content;
		if (!p->completed)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

int		wait_for_job(t_job *j)
{
	int			status;
	pid_t		pid;
	int			last;

	last = -1;
	(void)j;
	signal(SIGCHLD, SIG_DFL);
	while (true)
	{
		pid = waitpid(-1, &status, WUNTRACED);
		if ((mark_process_status(pid, status, &last)) || job_is_complete(j))
			break ;
	}
	return (last);
}

void	launch_process(t_process_p process, int dofork)
{
	if (list_iter_int(process->io_list, (void *)apply_redir, dofork))
		return ;
	ft_check_exec(&process->argv);
	if (dofork)
		exit(1);
}

t_node_p	iter_in_order(t_node_p ptr, t_list **stock)
{
	while (ptr || *stock)
	{
		if (ptr)
		{
			PUSH(stock, ptr);
			ptr = ptr->left;
		}
		else
		{
			return (POP(stock));
		}
	}
	return (NULL);
}

int		do_pipe(t_process_p p1, t_process_p p2, int *io_pipe)
{
	t_io	*io_in[2];
	t_io	*io_out[2];

	if (pipe(io_pipe) == -1)
		exit(ft_print_error("21sh", ERR_PIPE, ERR_EXIT));
	io_in[0] = new_io();
	io_in[1] = new_io();
	io_out[0] = new_io();
	io_out[1] = new_io();

	io_in[0]->tab_fd[0] = dup(STDOUT_FILENO);
	io_out[0]->tab_fd[1] = dup(STDIN_FILENO);

	io_in[0]->flag = DUP | CLOSE;
	io_in[1]->flag = CLOSE;
	io_out[0]->flag = DUP | CLOSE;
	io_out[1]->flag = CLOSE;

	io_in[0]->dup_src = io_pipe[1];
	io_in[0]->dup_target = STDOUT_FILENO;
	io_in[1]->dup_src = io_pipe[0];
	io_out[0]->dup_src = io_pipe[0];
	io_out[0]->dup_target = STDIN_FILENO;
	io_out[1]->dup_src = io_pipe[1];

	PUSH(&(p1->io_list), io_in[0]);
	PUSH(&(p1->io_list), io_in[1]);
	PUSH(&(p2->io_list), io_out[0]);
	PUSH(&(p2->io_list), io_out[1]);
	return (io_pipe[1]);
}

int		make_children(t_process_p p)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	else if (pid < 0)
		exit(ft_print_error("21sh", ERR_FORK, ERR_EXIT));
	else
		p->pid = pid;
	return (pid);
}

void	exec_simple_command(t_process_p p, int dofork)
{
	if (dofork)
		if (make_children(p))
			return ;
	launch_process(p, dofork);
}

int		shouldfork(t_job *j, t_list *pipeline)
{
	int			dofork;
	t_process_p	p;

	dofork = 0;
	p = pipeline->content;
	if (pipeline->next || !(p->flag & BUILTIN))
	{
		dofork = 1;
		j->flag = WAIT;
	}
	return (dofork);
}

void	do_pipeline(t_job *job, t_list *pipeline)
{
	int			io_pipe[2];
	int			in;
	int			out;
	int			dofork;

	dofork = 0;
	in = STDIN_FILENO;
	dofork |= shouldfork(job, pipeline);
	while (pipeline)
	{
		out = (pipeline->next) ? do_pipe(pipeline->content,
		pipeline->next->content, io_pipe) : STDOUT_FILENO;
		exec_simple_command(pipeline->content, dofork);
		list_iter_int(((t_process_p)pipeline->content)->io_list, (void *)restore_fd, dofork);
		if (out != STDOUT_FILENO)
			close(out);
		if (in != STDIN_FILENO)
			close(in);
		in = io_pipe[0];
		delete_list(&(((t_process_p)pipeline->content)->io_list), &free);
		insert_link_bottom(&job->wait_process_list, new_link(memcpy(malloc(pipeline->content_size), pipeline->content, pipeline->content_size), pipeline->content_size));
		pipeline = pipeline->next;
	}
}
 
void	launch_job(t_job *j)
{
	t_node_p	current;
	t_list		*stack;
	int			last;

	last = 0;
	current = j->process_tree;
	stack = NULL;
	insert_link_bottom(&g_job_list, new_link(j, sizeof(*j)));
	while ((current = iter_in_order(current, &stack)))
	{
		if (current->type == IF)
		{
			current = ((((t_condition_if_p)current->data)->type == IF_OR &&
				last) || (((t_condition_if_p)current->data)->type == IF_AND &&
					!last)) ? current->right : NULL;
		}
		else
		{
			do_pipeline(j, current->data);
			current = current->right;
			last = wait_for_job(j);
		}
	}
}
