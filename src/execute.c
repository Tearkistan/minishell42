/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:19:50 by twatson           #+#    #+#             */
/*   Updated: 2026/01/15 17:09:32 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_heredoc_mode(t_pipex *pipex, t_redirects *redir, t_shell *sh)
{
	heredoc_read(redir, pipex, sh);
	pipex->infile = pipex->pipe_fd[0];
	pipex->prev_fd = pipex->infile;
	return (0);
}

static int	init_norm_mode(t_pipex *pipex, t_redirects *redir)
{
	if (redir->type == IN)
	{
		pipex->infile = open(redir->target, O_RDONLY);
		if (pipex->infile < 0)
			perror("norm infile");
		pipex->prev_fd = pipex->infile;
	}		
	else if (redir->type == OUT)
	{
		pipex->outfile = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->outfile < 0)
			perror_exit("norm outfile");
	}
	else if (redir->type == APPEND)
	{
		pipex->outfile = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (pipex->outfile < 0)
			perror_exit("norm outfile");	
	}
	else
		return (perror("norm mode redir parsing error"), 1);
	return (0);
}

static int	init_redirects(t_redirects *redir, t_shell *shell, t_pipex *pipex)
{
	t_redirects	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == HEREDOC)
			init_heredoc_mode(pipex, curr, shell);
		else
			init_norm_mode(pipex, curr);
		curr = curr->next;
	}
	(void)shell;
	return (0);
}

int execute_line(t_pipeline *pipeline, t_shell *shell)
{
	t_pipex		pipex;
	t_pipeline	*curr;
	
	curr = pipeline;
	while (curr)
	{
		init_redirects(&curr->cmd.redirects, shell, &pipex);
		curr = curr->next;
	}
	return (0);
}
