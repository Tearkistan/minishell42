/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:37:27 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/26 15:42:06 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Subject says [pwd with no options]
// opion 1: just print the current working directory, ignoring any arguments
// opion 2: print an error message and return failure if there are any arguments

// We picked option 1

int	exec_pwd(char **cmd_args)
{
	char	*cwd;

	if (!cmd_args)
		return (EXIT_FAILURE); // should not happen, but just in case
	if (!cmd_args[0] || ft_strcmp(cmd_args[0], "pwd") != 0)
		return (error_msg("not the pwd command\n"), EXIT_FAILURE); // not the pwd command
	if (cmd_args[1])
		return (error_msg("pwd: too many arguments\n"), EXIT_FAILURE); // pwd should not have any arguments
	cwd = getcwd(NULL, 0); // dynamically allocate a buffer for the current working directory
	if (!cwd)
		return (error_msg("pwd"), FAILURE); // or memory allocation error
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}
