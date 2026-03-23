/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:37:27 by psmolich          #+#    #+#             */
/*   Updated: 2026/03/23 08:01:20 by psmolich         ###   ########.fr       */
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
		return (EXIT_FAILURE);
	if (!cmd_args[0] || ft_strcmp(cmd_args[0], "pwd") != 0)
		return (error_msg("not the pwd command\n"), EXIT_FAILURE);
	if (cmd_args[1])
		return (error_msg("pwd: too many arguments\n"), EXIT_FAILURE);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (error_msg("pwd"), FAILURE);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}
