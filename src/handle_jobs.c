/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_jobs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaffile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:15:02 by llaffile          #+#    #+#             */
/*   Updated: 2017/04/13 15:36:40 by alallema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "io.h"
#include "job.h"
#include <errno.h>

extern	t_list	*job_list;
int last = 0;

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

	ptr_job = job_list;
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

	ptr_job = job_list;
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

int	mark_process_status(pid_t pid, int status)
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
				last = WEXITSTATUS(status);
				if (WIFSIGNALED(status))
				{
					ft_putstr_fd("21sh: Terminated by signal ", 2);
					ft_putnbr_fd(WTERMSIG(status), 2);
					ft_putchar_fd('\n', 2);
				}
			}
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

void	wait_for_job(t_job *j)
{
	int			status;
	pid_t		pid;

	(void)j;
	signal(SIGCHLD, SIG_DFL);
	while (true)
	{
		pid = waitpid(-1, &status, WUNTRACED);// | WNOHANG);
		last = WEXITSTATUS(status);
		if (mark_process_status(pid, status))
			break ;
	}
}

void	launch_process(t_process_p process, int dofork)
{
	list_iter(process->io_list, (void *)apply_redir);
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
			return (POP(stock));
	}
	return (NULL);
}

void	apply_redir(t_io *io)
{
	int		pipefd[2];

	if (io->flag & OPEN)
	{
		if (io->flag & CLOSE && access(io->str, X_OK) == -1)
			io->dup_src = open(io->str, io->mode, DEF_FILE);
		if (io->dup_src < 0)
		{
			ft_putstr_fd("21sh: No such file or directory (a placer dans les error)\n", 2);
			exit(1);
		}
	}
	if (io->flag & WRITE)
	{
		pipe(pipefd);
		io->dup_src = pipefd[0];
		write(pipefd[1], io->str, ft_strlen(io->str));
		close(pipefd[1]);
	}
	if (io->flag & DUP)
	{
		if (fcntl(io->dup_src, F_GETFL) < 0/* && errno == EBADF (Bad file descriptor)*/)
		{
			ft_putstr_fd("21sh: Bad file descriptor (a placer dans les error)\n", 2);
			exit(1);
		}
		else
			dup2(io->dup_src, io->dup_target);
	}
	if (io->flag & CLOSE && io->flag ^ WRITE)
		close(io->dup_src);
}

int		do_pipe(t_process_p p1, t_process_p p2, int *io_pipe)
{
	t_io	*io_in;
	t_io	*io_out;

	if (pipe(io_pipe) == -1)
	{
		ft_putstr_fd("21sh: error pipe \n", 2);
		exit(1);
	}
	io_in = new_io();
	io_out = new_io();
	io_in->tab_fd[0] = dup(STDOUT_FILENO);
	io_out->tab_fd[1] = dup(STDIN_FILENO);
	io_in->flag = DUP | CLOSE;
	io_out->flag = DUP | CLOSE;
	io_in->dup_src = io_pipe[1];
	io_in->dup_target = STDOUT_FILENO;
	io_out->dup_src = io_pipe[0];
	io_out->dup_target = STDIN_FILENO;
	PUSH(&(p1->io_list), io_in);
	PUSH(&(p2->io_list), io_out);
	return (io_pipe[1]);
}

int		make_children(t_process_p p)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
//		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	else if (pid < 0)
	{
		ft_putstr_fd("21sh: error fork\n", 2);
		exit(1);
	}
	else
	{
		p->pid = pid;
	}
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
	int			dofork = 0;

	in = STDIN_FILENO;
	dofork |= shouldfork(job, pipeline);
	while (pipeline)
	{
		out = (pipeline->next)? do_pipe(pipeline->content, pipeline->next->content, io_pipe) : STDOUT_FILENO;
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

	current = j->process_tree;
	stack = NULL;
	while ((current = iter_in_order(current, &stack)))
	{
		if (current->type == IF)
			current = ((((t_condition_if_p)current->data)->type == IF_OR && last) || (((t_condition_if_p)current->data)->type == IF_AND && !last)) ? current->right : NULL;
		else
		{
			do_pipeline(j, current->data);
			current = current->right;
		}
	}
	insert_link_bottom(&job_list, new_link(j, sizeof(*j)));
	wait_for_job(j);
}
