/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:18:21 by twatson           #+#    #+#             */
/*   Updated: 2026/03/30 12:22:36 by twatson          ###   ########.fr       */
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