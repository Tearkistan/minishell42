/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:13:33 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 15:16:23 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// We need to talk about how to handle [env with no options or arguments]
// opion 1: just print the environment variables, ignoring any arguments
// opion 2: print an error message and return failure if there are any arguments

// env - print the environment
int	exec_env(char **cmd_args, char **envp)
{
	int	i;

	if (!cmd_args)
		return (FAILURE); // should not happen, but just in case
	if (!cmd_args[0] || ft_strcmp(cmd_args[0], "env") != 0)
		return (error_msg("not the env command"), FAILURE); // not the env command
	if (cmd_args[1])
		return (error_msg("env: too many arguments"), FAILURE); // env should not have any arguments
	i = 0;
	while (envp[i]) // print each environment variable
		ft_putendl_fd(envp[i++], STDOUT_FILENO);
	return (SUCCESS);
}
