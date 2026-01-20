/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:24:43 by twatson           #+#    #+#             */
/*   Updated: 2026/01/19 15:21:38 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_pipeline *pline, t_shell *sh, t_pipe *pipex)
{
	infile_guard(pipex);
	if (dup2(pipex->prev_fd, 0) == -1)
		perror_exit("dup2 prev_fd->stdin");
	close(pipex->prev_fd);
	if (pline->next)
	{
		if (dup2(pipex->pipe_fd[1], 1) == -1)
			perror_exit("dup2 pipe->stdout");
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
	}
	else
	{
		if (dup2(pipex->outfile, 1) == -1)
			perror_exit("dup2 outfile->stdout");
		close(pipex->outfile);
	}
	exec_cmd(pline->cmd.args, sh->envp);
}

static void	parent(t_pipeline *pline, t_shell *sh, t_pipe *pipex, pid_t pid)
{
	if (pline->next)
	{
		close(pipex->pipe_fd[1]);
		close(pipex->prev_fd);
		pipex->prev_fd = pipex->pipe_fd[0];
	}
	else
	{
		pipex->last_pid = pid;
		close(pipex->prev_fd);
	}
	(void)sh;
}

static int	cmd_stage(t_pipeline *pipeline, t_shell *shell, t_pipe *pipex)
{
	pid_t	pid;

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
	if (pid == 0)
		child(pipeline, shell, pipex);
	if (pid > 0)
	{	
		pipex->pids[pipex->n_spawned - 1] = pid;
		parent(pipeline, shell, pipex, pid);
	}
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
	while (i < pipex->cmd_count)
	{
		wait(NULL);
		i++;
	}
	shell->last_status = status_to_exitcode(status);
	return (0);
}	
/*		
		if (init_redirects(&curr->cmd.redirects, shell, pipex) == 1)
			return (0);
		execute_cmd(curr, shell, pipex);
		
	}
	return (0);
}
*/
