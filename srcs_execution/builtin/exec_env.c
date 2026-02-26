/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:13:33 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/26 15:42:26 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// We need to talk about how to handle [env with no options or arguments]
// opion 1: just print the environment variables, ignoring any arguments
// opion 2: print an error message and return failure if there are any arguments

// We picked option 2

// env - print the environment
int	exec_env(char **cmd_args, char **envp)
{
	int	i;

	if (!cmd_args)
		return (EXIT_FAILURE);
	if (!cmd_args[0] || ft_strcmp(cmd_args[0], "env") != 0)
		return (error_msg("not the env command"), EXIT_FAILURE);
	if (cmd_args[1])
		return (error_msg("env: shouldn't have any arguments"), EXIT_FAILURE);
	i = 0;
	while (envp[i])
		ft_putendl_fd(envp[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
