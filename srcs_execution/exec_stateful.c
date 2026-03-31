/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_stateful.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:23:44 by twatson           #+#    #+#             */
/*   Updated: 2026/03/31 13:35:22 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* exits shell if exit as single command */

static int	stateful_redirects(t_pipeline *pipeline, t_shell *shell,
	t_pipe *pipex)
{
	if (count_heredoc(pipeline->cmd.redirects))
	{
		if (init_heredoc_mode(pipex, pipeline->cmd.redirects, shell) == -1)
			return (abort_pipeline_parent(pipex, shell, 1));
	}
	if (search_builtin_in_fd(pipeline, pipex))
		return (abort_pipeline_parent(pipex, shell, 1));
	if (search_builtin_out_fd(pipeline, pipex))
		return (abort_pipeline_parent(pipex, shell, 1));
	if (pipex->in_fd != STDIN_FILENO)
	{
		if (dup2(pipex->in_fd, 0) == -1)
			return (perror_parent_exit(shell, pipex, "dup2 in_fd->stdin", 1));
		close_fd(&pipex->in_fd);
	}
	if (pipex->out_fd != STDOUT_FILENO)
	{
		if (dup2(pipex->out_fd, 1) == -1)
			return (perror_parent_exit(shell, pipex, "dup2 out_fd->stdout", 1));
		close_fd(&pipex->out_fd);
	}
	abort_pipeline_parent(pipex, shell, 0);
	return (0);
}

int	exec_stateful_builtin(t_pipeline *pline, t_shell *shell, t_pipe *pipex)
{
	int		saved_stdin;
	int		saved_stdout;

	set_signals_parent_running();
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (perror_parent_exit(shell, pipex, "dup saved_stdin", 1));
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
		return (perror_parent_exit(shell, pipex, "dup saved_stdout", 1));
	if (stateful_redirects(pline, shell, pipex) == 0)
		builtin_exec(pline->cmd.args, shell, 1);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return (perror_parent_exit(shell, pipex, "dup2 saved_stdin", 1));
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (perror_parent_exit(shell, pipex, "dup2 saved_stdout", 1));
	close_fd(&saved_stdin);
	close_fd(&saved_stdout);
	if (ft_strncmp(pline->cmd.args[0], "exit", 5) == 0)
		clean_up(shell, pline, NULL, "42");
	return (0);
}
