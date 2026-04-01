/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:19:50 by twatson           #+#    #+#             */
/*   Updated: 2026/03/31 13:33:35 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char **cmd_args, t_pipeline *head, t_pipe *pipex, t_shell \
*shell)
{
	char	*path;

	if (pipex->infile_stop)
		clean_exit_child(pipex, head, shell, 1);
	if (contains_path(cmd_args[0]))
		path_check_to_execute(cmd_args, head, shell, pipex);
	path = find_path(cmd_args, head, shell, pipex);
	if (!path)
	{
		error_msg("Command not found", NULL);
		clean_exit_child(pipex, head, shell, 127);
	}
	if (execve(path, cmd_args, shell->envp) == -1)
	{
		free(path);
		perror("execve");
		clean_exit_child(pipex, head, shell, 1);
	}
	free(path);
}

int	is_stateful(char *cmd)
{
	if (!cmd)
		return (0);
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

void	init_pipex(t_pipe *pipex, t_pipeline *pipeline, t_shell *shell,
			int alloc)
{
	pipex->last_pid = -1;
	pipex->infile_stop = 0;
	pipex->prev_read_fd = STDIN_FILENO;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->hd_fd = -1;
	pipex->hd_pipe[0] = -1;
	pipex->hd_pipe[1] = -1;
	pipex->in_error_switch = 0;
	pipex->cmd_count = pipeline_size(pipeline);
	pipex->n_spawned = 0;
	if (alloc)
	{
		pipex->pids = (int *)malloc(sizeof(int) * (pipex->cmd_count));
		if (!pipex->pids)
			clean_up(shell, pipeline, "pids array - memory allocation fail");
	}
	else
		pipex->pids = NULL;
	pipex->dirs = NULL;
	return ;
}

int	execute_line(t_pipeline *pipeline, t_shell *shell)
{
	t_pipe		pipex;

	if (!pipeline->next && pipeline->cmd.args
		&& is_stateful(pipeline->cmd.args[0]))
	{
		init_pipex(&pipex, pipeline, shell, 0);
		exec_stateful_builtin(pipeline, shell, &pipex);
	}
	else
	{
		init_pipex(&pipex, pipeline, shell, 1);
		exec_pipeline(pipeline, shell, &pipex);
	}
	set_signals_prompt_mode();
	return (0);
}
