/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:02:27 by twatson           #+#    #+#             */
/*   Updated: 2026/03/23 14:40:52 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	path_check_to_execute(char **cmd_args, t_pipeline *head, t_shell *shell\
, t_pipe *pipex)
{
	if (access(cmd_args[0], F_OK) == 0)
	{
		if (access(cmd_args[0], X_OK) == -1)
		{
			error_msg("Permission denied", NULL);
			clean_exit_child(pipex, head, shell, 126);
		}
	}
	else
	{
		error_msg("Command not found\n", NULL);
		clean_exit_child(pipex, head, shell, 127);
	}
	if (execve(cmd_args[0], cmd_args, shell->envp) == -1)
	{
		perror("execvce");
		clean_exit_child(pipex, head, shell, 1);
	}
	exit (0);
}
