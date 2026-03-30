/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:56:08 by twatson           #+#    #+#             */
/*   Updated: 2026/03/30 12:42:07 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_default_out_fd(t_pipe *pipex)
{
	if (pipex->n_spawned == pipex->cmd_count)
		pipex->out_fd = STDOUT_FILENO;
	else
	{
		if (pipex->pipe_fd[1] >= 0)
			pipex->out_fd = pipex->pipe_fd[1];
		else
			pipex->out_fd = STDOUT_FILENO;
	}
	return ;
}

void	set_in_fd(t_redirects *redir, t_pipe *pipex, t_pipeline *head,
			t_shell *shell)
{
	t_redirects	*last_in;

	pipex->in_fd = pipex->prev_read_fd;
	if (in_fail(redir, pipex))
		perror_child_exit(pipex, head, shell, "openning prior IN targets");
	last_in = last_in_finder(redir);
	if (last_in == NULL || last_in->type == REDIR_IN)
		close_fd(&pipex->hd_fd);
	if (last_in && last_in->type == REDIR_IN)
	{
		if (pipex->in_fd != STDIN_FILENO)
			close_fd(&pipex->in_fd);
		pipex->in_fd = open(last_in->target, O_RDONLY);
		if (pipex->in_fd < 0)
			perror_child_exit(pipex, head, shell, "setting IN in_fd");
	}
	else if (last_in && last_in->type == HEREDOC)
	{
		if (pipex->in_fd != STDIN_FILENO)
			close_fd(&pipex->in_fd);
		pipex->in_fd = pipex->hd_fd;
	}
	infile_guard(pipex);
	set_default_out_fd(pipex);
	return ;
}

void	set_out_fd(t_redirects *redir, t_pipe *pipex, t_pipeline *head,
			t_shell *shell)
{
	t_redirects	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == REDIR_OUT)
		{
			if (pipex->out_fd != STDOUT_FILENO)
				close_fd(&pipex->out_fd);
			pipex->out_fd = open(curr->target, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
			if (pipex->out_fd < 0)
				perror_child_exit(pipex, head, shell, "openning OUT out_fd");
		}
		else if (curr->type == REDIR_APP)
		{
			if (pipex->out_fd != STDOUT_FILENO)
				close_fd(&pipex->out_fd);
			pipex->out_fd = open(curr->target, O_CREAT | O_WRONLY | O_APPEND,
					0644);
			if (pipex->out_fd < 0)
				perror_child_exit(pipex, head, shell, "openning APPEND out_fd");
		}
		curr = curr->next;
	}
}

void	infile_guard(t_pipe *pipex)
{
	if (pipex->in_fd >= 0)
		return ;
	pipex->in_fd = open("/dev/null", O_RDONLY);
	if (pipex->in_fd < 0)
		perror_exit("open /dev/null");
	pipex->infile_stop = 1;
}

void	close_pipe(int pipe[2])
{
	close_fd(&pipe[0]);
	close_fd(&pipe[1]);
}
