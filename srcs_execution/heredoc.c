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

int	count_heredoc(t_redirects *redir)
{
	int			count;
	t_redirects	*curr;

	curr = redir;
	count = 0;
	while (curr)
	{
		if (curr->type == HEREDOC)
			count++;
		curr = curr->next;
	}
	return (count);
}

int	init_heredoc_mode(t_pipe *pipex, t_redirects *redir, t_shell *shell)
{
	t_redirects	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			if (pipe(pipex->hd_pipe) == -1)
				return (perror_int("heredoc pipe", -1));
			if (heredoc_read(curr, pipex, shell) == -1)			
				return (-1);
			pipex->hd_fd = pipex->hd_pipe[0];
		}
		curr = curr->next;
	}
	return (0);
}

int	heredoc_read(t_redirects *redir, t_pipe *pipex, t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (g_sig == SIGINT)
		{
			resolve_heredoc_sigint(line, shell, pipex);
			return (-1);
		}
		line = readline("> ");
		if (!line)
			return (perror_int("heredoc line allocation fail", -1));
		if (ft_strncmp(line, redir->target, ft_strlen(redir->target)) == 0)
		{
			free(line);
			break ;
		}
		if (redir->quote_delim == 1)
			/* INSERT */ (void)shell, ft_printf("INSERT function that utilizes parser environment variable expansion function here");
		if (write(pipex->hd_pipe[1], line, ft_strlen(line)) == -1)
			return (write_pipe_exit(pipex->hd_pipe, "write heredoc fail", -1));
		free(line);
	}
	close(pipex->hd_pipe[1]);
	return (0);
}
