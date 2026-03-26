/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:24:43 by twatson           #+#    #+#             */
/*   Updated: 2026/03/25 14:56:24 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_pipeline *curr, t_pipeline *head, t_shell *shell,
	t_pipe *pipex)
{
	set_signals_child();
	set_in_fd(curr->cmd.redirects, pipex);
	set_out_fd(curr->cmd.redirects, pipex);
	if (pipex->in_fd != STDIN_FILENO)
	{
		if (dup2(pipex->in_fd, 0) == -1)
			perror_exit("dup2 in_fd->stdin");
		close(pipex->in_fd);
		pipex->in_fd = -1;
	}
	if (pipex->out_fd != STDOUT_FILENO)
	{
		if (dup2(pipex->out_fd, 1) == -1)
			perror_exit("dup2 out_fd->stdout");
		if (!curr->next)
		{
			close(pipex->out_fd);
			pipex->out_fd = -1;
		}
	}
	if (curr->next)
		close_pipe(pipex->pipe_fd);
	if (is_builtin(curr->cmd.args[0]))
	{
		builtin_exec(curr->cmd.args, shell, 0);
		clean_exit_child(pipex, head, shell, 0);
	}
	else
		exec_cmd(curr->cmd.args, head, pipex, shell);
}

static void	parent(t_pipeline *pline, t_pipe *pipex, pid_t pid)
{
	pipex->pids[pipex->n_spawned - 1] = pid;
	if (pline->next)
	{
		close(pipex->pipe_fd[1]);
		pipex->pipe_fd[1] = -1;
		if (pipex->prev_read_fd >= 0 && pipex->prev_read_fd != STDIN_FILENO)
			close(pipex->prev_read_fd);
		pipex->prev_read_fd = pipex->pipe_fd[0];
		pipex->pipe_fd[0] = -1;
	}
	else
	{
		pipex->last_pid = pid;
		if (pipex->prev_read_fd >= 0 && pipex->prev_read_fd != STDIN_FILENO)
		{
			close(pipex->prev_read_fd);
			pipex->prev_read_fd = -1;
		}
	}
}

static int	cmd_stage(t_pipeline *curr, t_pipeline *head,
	t_shell *shell, t_pipe *pipex)
{
	pid_t	pid;

	if (count_heredoc(curr->cmd.redirects))
	{
		if (init_heredoc_mode(pipex, curr->cmd.redirects, shell) == -1)
			return (abort_pipeline_parent(pipex, shell, 1));
	}
	if (curr->next && (pipe(pipex->pipe_fd) == -1))
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
	if (pid == 0)
		child(curr, head, shell, pipex);
	if (pid > 0)
		parent(curr, pipex, pid);
	return (0);
}

int	exec_pipeline(t_pipeline *pipeline, t_shell *shell, t_pipe *pipex)
{
	t_pipeline	*curr;
	int			status;
	int			i;

	curr = pipeline;
	status = 0;
	i = 0;
	set_signals_parent_running();
	while (curr)
	{
		if (cmd_stage(curr, pipeline, shell, pipex) != 0)
			break ;
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
	int			i;
	t_pipeline	*curr;

	curr = p;
	i = 0;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
