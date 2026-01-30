/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:19:50 by twatson           #+#    #+#             */
/*   Updated: 2026/01/20 19:02:51 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char **cmd_args, char **envp)
{
	char	*path;

	path = find_path(cmd_args, cmd_args[0], envp);
	if (!path)
		not_found_exit(cmd_args);
	if (execve(path, cmd_args, envp) == -1)
	{
		free(path);
		free_matrix(cmd_args);
		perror_exit("execve");
	}
	free(path);
}

int	is_stateful(char *cmd)
{
	if (ft_strlen(cmd) >= 2 && ft_strncmp(cmd, "cd", 3))
		return (1);
	if (ft_strlen(cmd) >= 4 && ft_strncmp(cmd, "exit", 5))
		return (1);
	if (ft_strlen(cmd) >= 5 && ft_strncmp(cmd, "unset", 6))
		return (1);
	if (ft_strlen(cmd) >= 6 && ft_strncmp(cmd, "export", 7))
		return (1);
	return (0);
}

int	is_nonstateful(char *cmd)
{
	if (ft_strlen(cmd) >= 3 && ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (ft_strlen(cmd) >= 4 && ft_strncmp(cmd, "envp", 5))
		return (1);
	if (ft_strlen(cmd) >= 4 && ft_strncmp(cmd, "echo", 5))
		return (1);
	return (0);
}

static void	init_pipex(t_pipe *pipex, t_pipeline *pipeline, t_shell *shell)
{
	pipex->last_pid = -1;
	pipex->prev_read_fd = STDIN_FILENO;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->cmd_count = pipeline_size(pipeline);
	pipex->n_spawned = 0;
	pipex->pids = (int *)malloc(sizeof(int) * (pipex->cmd_count));
	if (!pipex->pids)
		clean_up(shell, pipeline, NULL, "pids array - memory allocation fail");
	return ;
}

int execute_line(t_pipeline *pipeline, t_shell *shell)
{
	t_pipe		pipex;

	return (0); // remove to actually test excution
	init_pipex(&pipex, pipeline, shell);
	if (!pipeline->next && is_stateful(pipeline->cmd.args[0]))
		exec_stateful_builtin(pipeline, shell, &pipex);
	else
		exec_pipeline(pipeline, shell, &pipex);
	set_signals_prompt_mode();
	return (0);
}
