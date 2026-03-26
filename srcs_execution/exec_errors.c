/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:25:36 by twatson           #+#    #+#             */
/*   Updated: 2026/03/26 14:56:07 by twatson          ###   ########.fr       */
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
		close(pipex->hd_fd);
	if (pipex->pipe_fd[0] >= 0)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] >= 0)
		close(pipex->pipe_fd[1]);
	if (pipex->prev_read_fd >= 0 && pipex->prev_read_fd != STDIN_FILENO)
		close(pipex->prev_read_fd);
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

void	perror_in_fd(char *err_msg, t_pipe *pipex)
{
	if (!pipex->in_error_switch)
		perror(err_msg);
	pipex->in_error_switch = 1;
}

/*int	write_pipe_exit(int pipe[2], char *s, int n)
{
	close(pipe[0]);
	close(pipe[1]);
	return (perror_int(s, n));
}*/
