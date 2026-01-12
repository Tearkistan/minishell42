/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:20:08 by mnussler          #+#    #+#             */
/*   Updated: 2025/09/20 16:20:09 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Frees dynamically allocated argument array
 * @param argv Array of command arguments to free
 */
void	free_cmd_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/**
 * @brief Frees command structure and its allocated memory
 * @param cmd Command structure to free
 */
void	free_cmd(t_cmd *cmd)
{
	if (cmd->argv)
		free_cmd_argv(cmd->argv);
	if (cmd->path)
		free(cmd->path);
	cmd->argv = NULL;
	cmd->path = NULL;
}

/**
 * @brief Cleans up pipex structure: frees memory and closes files
 * @param px Pipex structure to clean up
 */
void	cleanup_pipex(t_pipex *px)
{
	free_cmd(&px->cmd1);
	free_cmd(&px->cmd2);
	close_files(px);
}

/**
 * @brief Prints error message and exits with status 127
 * @param msg Error message to display
 * @param px Optional pipex structure to cleanup (can be NULL)
 */
void	exit_error(char *msg, t_pipex *px)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (px)
		cleanup_pipex(px);
	exit(1);
}
