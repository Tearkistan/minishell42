/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:02:27 by twatson           #+#    #+#             */
/*   Updated: 2026/02/17 13:06:58 by twatson          ###   ########.fr       */
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

void	path_check_to_execute(char **cmd_args, char *cmd, char **envp)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
			permission_denied_exit(cmd_args);
	}
	else
		not_found_exit(cmd_args);
	if (execve(cmd, cmd_args, envp) == -1)
		perror_exit("execvce");
	exit (0);
}
