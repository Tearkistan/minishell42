/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:32:37 by twatson           #+#    #+#             */
/*   Updated: 2026/01/16 16:37:33 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signals_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = signint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	resolve_prompt_sigint(t_shell *shell)
{
	g_sig = 0;
	shell->last_status = 130;
	return ;
}

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
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
