/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:20:29 by mnussler          #+#    #+#             */
/*   Updated: 2025/09/20 16:20:30 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Opens input file for reading with robust error handling
 * @param filename Path to the input file
 * @return File descriptor for reading
 *
 * @note Error handling for missing files
 *
 * - If filename cannot be opened, print error to stderr
 *
 * - Continue execution (don't exit on input redirection failure)
 *
 * - Use /dev/null as fallback to prevent blocking pipeline
 *
 * - Only exits on system errors (/dev/null failure)
 */
int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
		{
			perror("/dev/null");
			exit(1);
		}
	}
	return (fd);
}

/**
 * @brief Opens output file for writing with create/truncate behavior
 * @param filename Path to the output file
 * @return File descriptor for writing
 *
 * @note
 * Opens with O_CREAT | O_TRUNC | O_WRONLY flags:
 * - Creates file if it doesn't exist with 0644 permissions (rw-r--r--)
 * - Truncates existing file to length 0
 * - Write-only access mode
 * - Exits with perror on failure
 */
int	open_output_file(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror(filename);
		exit(1);
	}
	return (fd);
}

/**
 * @brief Closes all file descriptors in pipex structure safely
 * @param px Pipex structure containing file descriptors to close
 */
void	close_files(t_pipex *px)
{
	if (!px)
		return ;
	if (px->infile >= 0)
		close(px->infile);
	if (px->outfile >= 0)
		close(px->outfile);
	if (px->pipe_fd[0] >= 0)
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] >= 0)
		close(px->pipe_fd[1]);
}
