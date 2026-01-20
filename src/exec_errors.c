/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:25:36 by twatson           #+#    #+#             */
/*   Updated: 2026/01/20 19:15:59 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	permission_denied_exit(char **cmd_args)
{
	ft_putendl_fd("Permission denied", 2);
	free_matrix(cmd_args);
	exit(126);
}

void	not_found_exit(char **cmd_args)
{
	ft_putendl_fd("Command not found", 2);
	free_matrix(cmd_args);
	exit(127);
}

int	abort_pipeline_parent(t_pipe *pipex, t_shell *shell, int status_code)
{
	int	i;

	if (pipex->pipe_fd[0] >= 0)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] >= 0)
		close(pipex->pipe_fd[1]);
	if (pipex->prev_fd >= 0 && pipex->prev_fd != STDIN_FILENO)
		close(pipex->prev_fd);
	i = 0;
	while (i < pipex->n_spawned)
	{
		if (pipex->pids[i] > 0)
			waitpid(pipex->pids[i], NULL, 0);
		i++;
	}
	shell->last_status = status_code;
	return (-1);
}
