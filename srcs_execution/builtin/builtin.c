/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:55:01 by twatson           #+#    #+#             */
/*   Updated: 2026/04/01 11:36:46 by twatson          ###   ########.fr       */
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

int	append_shell_envp(t_shell *shell, char *new_line)
{
	char	**new_envp;

	new_envp = (char **)malloc(sizeof(char *) * (shell->envp_len + 2));
	if (!new_envp)
		return (1);
	new_envp = copy_envp(new_envp, shell->envp, 0);
	new_envp[shell->envp_len] = new_line;
	new_envp[shell->envp_len + 1] = NULL;
	shell->envp_len++;
	free_matrix(shell->envp);
	shell->envp = new_envp;
	return (0);
}

int	ft_strncmp_set(char *str, char **set)
{
	int	i;
	int	n;

	i = 0;
	while (set[i])
	{
		n = ft_strlen(set[i]);
		if (ft_strncmp(str, set[i], n) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	**copy_array(char **set)
{
	int		i;
	char	**copy;

	i = 0;
	while (set[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	copy[i] = NULL;
	i = 0;
	while (set[i])
	{
		copy[i] = ft_strdup(set[i]);
		if (!copy)
			return (NULL);
		i++;
	}
	return (copy);
}

int	builtin_exec(char **args, t_shell *shell, int parent)
{
	if (!ft_strcmp(args[0], "cd"))
		return (exec_cd_ctrl(args, shell, parent));
	else if (!ft_strcmp(args[0], "exit"))
		return (exec_exit(args, shell, parent));
	else if (!ft_strcmp(args[0], "unset"))
		return (exec_unset_ctrl(args, shell, parent));
	else if (!ft_strcmp(args[0], "export"))
		return (exec_export_ctrl(args, shell, parent));
	else if (!ft_strcmp(args[0], "pwd"))
		return (exec_pwd(args));
	else if (!ft_strcmp(args[0], "env"))
		return (exec_env(args, shell->envp));
	else if (!ft_strcmp(args[0], "echo"))
		return (exec_echo(args));
	return (perror_int("built_in inflow issue", 1));
}
