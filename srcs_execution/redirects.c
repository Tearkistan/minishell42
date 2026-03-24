/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:56:08 by twatson           #+#    #+#             */
/*   Updated: 2026/03/24 06:37:29 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_in_fd(t_redirects *redir, t_pipe *pipex)
{
	t_redirects	*curr;

	pipex->in_fd = pipex->prev_read_fd;
	curr = redir;
	while (curr)
	{
		if (curr->type == REDIR_IN)
		{
			if (pipex->in_fd != STDIN_FILENO)
				close(pipex->in_fd);
			pipex->in_fd = open(curr->target, O_RDONLY);
			if (pipex->in_fd < 0)
				perror("setting IN in_fd");
		}
		else if (curr->type == HEREDOC)
		{
			if (pipex->in_fd != STDIN_FILENO)
				close(pipex->in_fd);
			pipex->in_fd = pipex->hd_fd;
		}
		curr = curr->next;
	}
	infile_guard(pipex);
	return ;
}

static void	set_default_out_fd(t_pipe *pipex)
{
	if (pipex->n_spawned == pipex->cmd_count)
		pipex->out_fd = STDOUT_FILENO;
	else
		pipex->out_fd = pipex->pipe_fd[1];
	return ;
}

void	set_out_fd(t_redirects *redir, t_pipe *pipex)
{
	t_redirects	*curr;

	set_default_out_fd(pipex);
	curr = redir;
	while (curr)
	{
		if (redir->type == REDIR_OUT)
		{
			if (pipex->out_fd != STDOUT_FILENO)
				close(pipex->out_fd);
			pipex->out_fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
			if (pipex->out_fd < 0)
				perror_exit("openning OUT out_fd");
		}
		else if (redir->type == REDIR_APP)
		{
			if (pipex->out_fd != STDOUT_FILENO)
				close(pipex->out_fd);
			pipex->out_fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND,
				0644);
			if (pipex->out_fd < 0)
				perror_exit("openning APPEND out_fd");
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
	close(pipe[0]);
	close(pipe[1]);
}
