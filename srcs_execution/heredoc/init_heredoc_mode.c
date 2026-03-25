/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heredoc_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 06:01:11 by psmolich          #+#    #+#             */
/*   Updated: 2026/03/25 15:40:39 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// close() returns zero on success.  On error, -1 is returned, and
//        errno is set to indicate the error.
static int	close_hd_pipes(t_pipe *pipex)
{
	if (pipex->hd_pipe[0] >= 0)
		if (close(pipex->hd_pipe[0]) == -1)
			return (FAILURE);
	if (pipex->hd_pipe[1] >= 0)
		if (close(pipex->hd_pipe[1]) == -1)
			return (FAILURE);
	return (SUCCESS);
}

int	init_heredoc_mode(t_pipe *pipex, t_redirects *redir, t_shell *sh)
{
	t_redirects	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			if (pipe(pipex->hd_pipe) == -1)
				return (perror_int("heredoc pipe", -1));
			set_signals_prompt_mode();
			if (heredoc_read(curr, pipex, sh) == -1)
			{
				set_signals_parent_running();
				if (close_hd_pipes(pipex) == FAILURE)
					perror(Y "MINIsHELL:" R);
				return (-1);
			}
			else if (pipex->hd_pipe[1] && close(pipex->hd_pipe[1]) == -1)
				perror(Y "MINIsHELL:" R);
			set_signals_parent_running();
			pipex->hd_fd = pipex->hd_pipe[0];
		}
		curr = curr->next;
	}
	return (0);
}
