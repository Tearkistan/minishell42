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

int	heredoc_read(t_redirects *redir, t_pipex *pipex, t_shell *shell)
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
