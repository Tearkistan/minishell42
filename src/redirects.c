/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:18:48 by twatson           #+#    #+#             */
/*   Updated: 2026/01/14 14:37:49 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_heredoc_mode(t_pipe *pipex, t_redirects *redir, t_shell *shell)
{
	if (heredoc_read(redir, pipex, shell) == 1)
		return (1);
	pipex->infile = pipex->pipe_fd[0];
	pipex->prev_fd = pipex->infile;
	return (0);
}

int	init_norm_mode(t_pipe *pipex, t_redirects *redir)
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

int	init_redirects(t_redirects *redir, t_shell *shell, t_pipe *pipex)
{
	t_redirects	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			if (init_heredoc_mode(pipex, curr, shell) == 1)
				return (1);
		}
		else
			init_norm_mode(pipex, curr);
		curr = curr->next;
	}
	return (0);
}

int	heredoc_read(t_redirects *redir, t_pipe *pipex, t_shell *shell)
{
	char	*line;

	if (pipe(pipex->pipe_fd) == -1)
		perror_exit("here_doc pipe");
	while (1)
	{
		ft_printf("> ");
		if (g_sig == SIGINT)
		{
			resolve_heredoc_sigint(line, shell, pipex);
			return (1);
		}
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, redir->target, ft_strlen(redir->target)) == 0)
		{
			free(line);
			break ;
		}
		if (redir->quote_delim == 1)
			/* INSERT */ (void)shell, ft_printf("INSERT parser environment variable expansion function here");
		write(pipex->pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipex->pipe_fd[1]);
	return (0);
}
