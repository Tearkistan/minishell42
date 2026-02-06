/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:55:01 by twatson           #+#    #+#             */
/*   Updated: 2026/01/30 14:32:43 by twatson          ###   ########.fr       */
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

int	append_shell_envp(t_shell *sh, int old_len, char *new_line, char **new_envp)
{
	new_envp = (char **)malloc(sizeof(char *) * (old_len + 1));
	if (!new_envp)
		return (1);
	copy_envp(new_envp, sh->envp, 0);
	new_envp[old_len] = new_line;
	new_envp[old_len + 1] = NULL;
	free(sh->envp);
	sh->envp = new_envp;
	return (0);
}

int	builtin_exec(char **args, t_shell *shell, int parent)
{
	if (ft_strlen(args[0]) >= 2 && ft_strncmp(args[0], "cd", 3))
		return (exec_cd_ctrl(args, shell, parent));
	else if (ft_strlen(args[0]) >= 4 && ft_strncmp(args[0], "exit", 5))
		return (exec_exit(args, shell));
	else if (ft_strlen(args[0]) >= 5 && ft_strncmp(args[0], "unset", 6))
		return (exec_unset(args, shell->envp));
	else if (ft_strlen(args[0]) >= 6 && ft_strncmp(args[0], "export", 7))
		return (exec_export(args, shell->envp));
	else if (ft_strlen(args[0]) >= 2 && ft_strncmp(args[0], "pwd", 4))
		return (exec_export(args, shell->envp));
	else if (ft_strlen(args[0]) >= 4 && ft_strncmp(args[0], "envp", 5))
		return (exec_envp(args, shell->envp));
	else if (ft_strlen(args[0]) >= 5 && ft_strncmp(args[0], "echo", 5))
		return (exec_echo(args, shell->envp));
	return (perror_int("built_in inflow issue", 1));
}
