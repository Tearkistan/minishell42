/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:25:36 by twatson           #+#    #+#             */
/*   Updated: 2026/03/30 12:42:20 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	permission_denied_exit(t_pipeline *head, t_shell *shell, t_pipe *pipex)
{
	error_msg("Permission denied", NULL);
	clean_exit_child(pipex, head, shell, 126);
}

int	perror_int(char *err_msg, int n)
{
	perror(err_msg);
	return (n);
}

int	abort_pipeline_parent(t_pipe *pipex, t_shell *shell, int stat_code)
{
	int	i;

	if (pipex->hd_fd >= 0)
		close_fd(&pipex->hd_fd);
	if (pipex->hd_pipe[0] >= 0)
		close_fd(&pipex->hd_pipe[0]);
	if (pipex->hd_pipe[1] >= 0)
		close_fd(&pipex->hd_pipe[1]);
	if (pipex->pipe_fd[0] >= 0)
		close_fd(&pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] >= 0)
		close_fd(&pipex->pipe_fd[1]);
	if (pipex->prev_read_fd >= 0 && pipex->prev_read_fd != STDIN_FILENO)
		close_fd(&pipex->prev_read_fd);
	i = 0;
	while (i < pipex->n_spawned)
	{
		if (pipex->pids[i] > 0)
			waitpid(pipex->pids[i], NULL, 0);
		i++;
	}
	shell->last_status = stat_code;
	return (-1);
}

void	perror_child_exit(t_pipe *pipex, t_pipeline *head, t_shell *shell,
			char *err_msg)
{
	perror(err_msg);
	clean_exit_child(pipex, head, shell, 1);
}
