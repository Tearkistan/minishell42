/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:24:43 by twatson           #+#    #+#             */
/*   Updated: 2026/01/26 16:50:05 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_pipeline *pline, t_shell *sh, t_pipe *pipex)
{
	
	set_in_fd(pline->cmd.redirects, pipex);
	set_out_fd(pline->cmd.redirects, pipex);
	if (dup2(pipex->in_fd, 0) == -1)
		perror_exit("dup2 in_fd->stdin");
	close(pipex->in_fd);
	if (dup2(pipex->out_fd, 1) == -1)
		perror_exit("dup2 out_fd->stdout");
	if (pline->next)
	{
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
	}
	else
	{
		close(pipex->out_fd);
	}
	if (is_builtin(pline->cmd.args[0]))
		builtin_exec(pline->cmd.args, sh->envp);
	else
		exec_cmd(pline->cmd.args, sh->envp);
}

static void	parent(t_pipeline *pline, t_pipe *pipex, pid_t pid)
{
	pipex->pids[pipex->n_spawned - 1] = pid;
	if (pline->next)
	{
		close(pipex->pipe_fd[1]);
		close(pipex->prev_read_fd);
		pipex->prev_read_fd = pipex->pipe_fd[0];
	}
	else
	{
		pipex->last_pid = pid;
		close(pipex->prev_read_fd);
	}
}

static int	cmd_stage(t_pipeline *pipeline, t_shell *shell, t_pipe *pipex)
{
	pid_t	pid;

	if (count_heredoc(pipeline->cmd.redirects))
	{
		if (init_heredoc_mode(pipex, pipeline->cmd.redirects, shell) == -1)
			return (abort_pipeline_parent(pipex, shell, 1));
	}
	if (pipeline->next && (pipe(pipex->pipe_fd) == -1))
	{
		perror("pipe");
		return (abort_pipeline_parent(pipex, shell, 1));
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (abort_pipeline_parent(pipex, shell, 1));
	}
	pipex->n_spawned++;
	set_signals_child();
	if (pid == 0)
		child(pipeline, shell, pipex);
	if (pid > 0)
		parent(pipeline, pipex, pid);
	return (0);
}

int	exec_pipeline(t_pipeline *pipeline, t_shell *shell, t_pipe *pipex)
{
	t_pipeline	*curr;
	int			status;
	int			i;

	curr = pipeline;
	i = 0;
	set_signals_parent_running();
	while (curr)
	{
		pipex->cmd_count++;
		if (cmd_stage(pipeline, shell, pipex) != 0)
			break;
		curr = curr->next;
	}
	waitpid(pipex->last_pid, &status, 0);
	while (i < pipex->n_spawned)
	{
		wait(NULL);
		i++;
	}
	shell->last_status = status_to_exitcode(status);
	free(pipex->pids);
	return (0);
}

int	pipeline_size(t_pipeline *p)
{
	int	i;

	i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	return (i);
}
