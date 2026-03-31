/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:18:21 by twatson           #+#    #+#             */
/*   Updated: 2026/03/31 13:27:45 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	not_last_redir(t_redirects *redir)
{
	if (redir->next->type == REDIR_IN || redir->next->type == HEREDOC)
		return (1);
	return (0);
}

int	in_fail(t_redirects *redir, t_pipe *pipex)
{
	t_redirects	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == REDIR_IN && not_last_redir(curr))
		{
			if (pipex->in_fd != STDIN_FILENO && pipex->in_fd != pipex->hd_fd)
				close_fd(&pipex->in_fd);
			pipex->in_fd = open(curr->target, O_RDONLY);
			if (pipex->in_fd < 0)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

t_redirects	*last_in_finder(t_redirects *redir)
{
	t_redirects	*last_in;
	t_redirects	*curr;

	last_in = NULL;
	curr = redir;
	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == HEREDOC)
			last_in = curr;
		curr = curr->next;
	}
	return (last_in);
}

int	search_builtin_in_fd(t_pipeline *pipeline, t_pipe *pipex)
{
	t_redirects	*last_in;

	pipex->in_fd = pipex->prev_read_fd;
	if (in_fail(pipeline->cmd.redirects, pipex))
		return (perror_int("openning prior IN targets", 1));
	last_in = last_in_finder(pipeline->cmd.redirects);
	if (last_in == NULL || last_in->type == REDIR_IN)
		close_fd(&pipex->hd_fd);
	if (last_in && last_in->type == REDIR_IN)
	{
		if (pipex->in_fd != STDIN_FILENO)
			close_fd(&pipex->in_fd);
		pipex->in_fd = open(last_in->target, O_RDONLY);
		if (pipex->in_fd < 0)
			return (perror_int("setting IN in_fd", 1));
	}
	else if (last_in && last_in->type == HEREDOC)
	{
		if (pipex->in_fd != STDIN_FILENO)
			close_fd(&pipex->in_fd);
		pipex->in_fd = pipex->hd_fd;
	}
	infile_guard(pipex);
	set_default_out_fd(pipex);
	return (0);
}

int	search_builtin_out_fd(t_pipeline *pipeline, t_pipe *pipex)
{
	t_redirects	*curr;
	int			flags;

	curr = pipeline->cmd.redirects;
	while (curr)
	{
		if (curr->type == REDIR_OUT || STDOUT_FILENO)
		{
			if (pipex->out_fd != STDOUT_FILENO)
				close_fd(&pipex->out_fd);
			flags = O_CREAT | O_WRONLY;
			if (curr->type == REDIR_APP)
				flags |= O_APPEND;
			else
				flags |= O_TRUNC;
			pipex->out_fd = open(curr->target, flags, 0644);
			if (pipex->out_fd < 0)
				return (perror_int("openning out_fd", 1));
		}
		curr = curr->next;
	}
	return (0);
}
