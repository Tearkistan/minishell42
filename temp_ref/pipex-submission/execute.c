/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:20:24 by mnussler          #+#    #+#             */
/*   Updated: 2025/09/20 16:20:24 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief First child process: reads from infile, writes to pipe
 * @param px Pipex structure containing file descriptors and commands
 *
 * @note Process flow
 *
 * - `dup2(infile, STDIN)` - redirects stdin to read from input file
 *
 * - `dup2(pipe[1], STDOUT)` - redirects stdout to write end of pipe
 *
 * - `close_files()` - closes unused file descriptors
 *
 * - `execve()` - replaces process with cmd1,
 *
 * - exits 127 (cmd not found) on failure
 */
void	child1_process(t_pipex *px)
{
	dup2(px->infile, STDIN_FILENO);
	dup2(px->pipe_fd[1], STDOUT_FILENO);
	close_files(px);
	execve(px->cmd1.path, px->cmd1.argv, px->envp);
	ft_putstr_fd(px->cmd1.argv[0], 2);
	if (errno == ENOENT)
		ft_putstr_fd(": command not found\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd(": permission denied\n", 2);
	else
		ft_putstr_fd(": command failed\n", 2);
	cleanup_pipex(px);
	exit(127);
}

/**
 * @brief Second child process: reads from pipe, writes to outfile
 * @param px Pipex structure containing file descriptors and commands
 *
 * @note Process flow
 *
 * - `dup2(pipe[0], STDIN)` - redirects stdin to read end of pipe
 *
 * - `dup2(outfile, STDOUT)` - redirects stdout to output file
 *
 * - `close_files()` - closes unused file descriptors
 *
 * - `execve()` - replaces process with cmd2,
 *
 * - exits 127 (cmd not found) on failure
 */
void	child2_process(t_pipex *px)
{
	dup2(px->pipe_fd[0], STDIN_FILENO);
	dup2(px->outfile, STDOUT_FILENO);
	close_files(px);
	execve(px->cmd2.path, px->cmd2.argv, px->envp);
	ft_putstr_fd(px->cmd2.argv[0], 2);
	if (errno == ENOENT)
		ft_putstr_fd(": command not found\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd(": permission denied\n", 2);
	else
		ft_putstr_fd(": command failed\n", 2);
	cleanup_pipex(px);
	exit(127);
}

/**
 * @brief Creates pipe for inter-process communication
 * @param px Pipex structure to store pipe file descriptors
 */
void	create_pipe(t_pipex *px)
{
	if (pipe(px->pipe_fd) == -1)
	{
		perror("pipe");
		cleanup_pipex(px);
		exit(1);
	}
}

/**
 * @brief Waits for both child processes to complete and returns the pipeline
 * exit status
 * @param pid1 Process ID of first child
 * @param pid2 Process ID of second child
 * @return Exit status (last command's exit code)
 *
 * @note
 *
 * - waitpid() returns a multi-value status value
 *
 * - WEXITSTATUS() extracts just the exit code (0-255) from this status
 */
int	wait_for_children(pid_t pid1, pid_t pid2)
{
	int	exit_code2;
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		exit_code2 = WEXITSTATUS(status2);
	else
		exit_code2 = 1;
	return (exit_code2);
}

/**
 * @brief Main pipeline execution: creates pipe, forks processes, waits
 * @param px Pipex structure containing all pipeline data
 * @return Exit status of the pipeline (last command's exit code)
 *
 * @note Execution flow
 *
 * 1. `create_pipe()` - creates pipe for IPC between processes
 *
 * 2. `fork()` first child → `pid1 == 0` runs child1_process()
 *
 * 3. `fork()` second child → `pid2 == 0` runs child2_process()
 *
 * 4. Parent process: `close_files()` then `wait_for_children()`
 *
 * 5. `waitpid()` blocks until both children complete
 *
 * Creates pipeline: `cmd1 < infile | cmd2 > outfile`
 */
int	execute_pipeline(t_pipex *px)
{
	pid_t	pid1;
	pid_t	pid2;

	create_pipe(px);
	pid1 = fork();
	if (pid1 == -1)
		exit_error("fork failed", px);
	if (pid1 == 0)
		child1_process(px);
	pid2 = fork();
	if (pid2 == -1)
		exit_error("fork failed", px);
	if (pid2 == 0)
		child2_process(px);
	close_files(px);
	return (wait_for_children(pid1, pid2));
}
