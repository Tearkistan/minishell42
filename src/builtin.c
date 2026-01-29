/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:55:01 by twatson           #+#    #+#             */
/*   Updated: 2026/01/26 16:58:18 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (is_stateful(cmd))
		return (1);
	if (is_nonstateful(cmd))
		return (1);
	return (0);
}

int	builtin_exec(t_pipe *pipex, char **cmd_args, char **envp)
{
	if (ft_strlen(cmd_args[0]) >= 2 && ft_strncmp(cmd_args[0], "cd", 3))
		return (exec_cd(pipex, cmd_args, envp));
	else if (ft_strlen(cmd_args[0]) >= 4 && ft_strncmp(cmd_args[0], "exit", 5))
		return (exec_exit(cmd_args, envp));
	else if (ft_strlen(cmd_args[0]) >= 5 && ft_strncmp(cmd_args[0], "unset", 6))
		return (exec_unset(cmd_args, envp));
	else if (ft_strlen(cmd_args[0]) >= 6 && ft_strncmp(cmd_args[0], "export", 7))
		return (exec_export(cmd_args, envp));
	else if (ft_strlen(cmd_args[0]) >= 2 && ft_strncmp(cmd_args[0], "pwd", 4))
		return (exec_export(cmd_args, envp));
	else if (ft_strlen(cmd_args[0]) >= 4 && ft_strncmp(cmd_args[0], "envp", 5))
		return (exec_envp(cmd_args, envp));
	else if (ft_strlen(cmd_args[0]) >= 5 && ft_strncmp(cmd_args[0], "echo", 5))
		return (exec_echo(cmd_args, envp));
	return (perror_int("built_in inflow issue", 1));
}
