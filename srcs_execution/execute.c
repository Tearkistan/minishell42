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

	if (contains_path(cmd_args[0]))
		path_check_to_execute(cmd_args, cmd_args[0], envp);
	path = find_path(cmd_args, cmd_args[0], envp);
	if (!path)
		not_found_exit(cmd_args);
	if (execve(path, cmd_args, envp) == -1)
	{
		free(path);
		perror_exit("execve");
	}
	free(path);
}

int	is_stateful(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	return (0);
}

int	is_nonstateful(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
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

	if (!pipeline->next && is_stateful(pipeline->cmd.args[0]))
		exec_stateful_builtin(pipeline, shell);
	else
	{
		init_pipex(&pipex, pipeline, shell);
		exec_pipeline(pipeline, shell, &pipex);
	}
	set_signals_prompt_mode();
	return (0);
}
