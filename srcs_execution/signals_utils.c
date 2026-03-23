/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:32:37 by twatson           #+#    #+#             */
/*   Updated: 2026/03/23 17:45:18 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	resolve_heredoc_sigint(char *line, t_shell *shell, t_pipe *pipex)
{
	g_sig = 0;
	free(line);
	close(pipex->pipe_fd[1]);
	shell->last_status = 130;
}

int	status_to_exitcode(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		return (130);
	}
	return (1);
}
