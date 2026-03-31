/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_plus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:21:40 by twatson           #+#    #+#             */
/*   Updated: 2026/03/31 22:46:51 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_no_eq(char *var, char **no_eq)
{
	int	i;

	i = 0;
	while (no_eq && no_eq[i])
	{
		if (ft_strcmp(var, no_eq[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	add_no_equal_key(t_export *export, t_shell *shell)
{
	int		i;
	char	**new_no_eq;

	i = 0;
	while (shell->no_eq && shell->no_eq[i])
		i++;
	new_no_eq = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_no_eq)
		exit_export(export, shell, 1);
	i = 0;
	while (shell->no_eq && shell->no_eq[i])
	{
		new_no_eq[i] = shell->no_eq[i];
		i++;
	}
	new_no_eq[i] = ft_strdup(export->key);
	if (!new_no_eq[i])
		exit_export(export, shell, 1);
	export->new_line = new_no_eq[i];
	i++;
	new_no_eq[i] = NULL;
	if (shell->no_eq)
		free(shell->no_eq);
	shell->no_eq = new_no_eq;
}

static void	renew_no_eq(t_shell *shell, t_export *export, int index, int len)
{
	int		i;
	int		j;
	char	**new_no_eq;

	i = 0;
	j = 0;
	new_no_eq = (char **)malloc(sizeof(char *) * len);
	if (!new_no_eq)
		exit_export(export, shell, 1);
	new_no_eq[len] = NULL;
	while (shell->no_eq[i])
	{
		if (i == index)
			i++;
		new_no_eq[j] = shell->no_eq[i];
		i++;
		j++;
	}
	free(shell->no_eq);
	shell->no_eq = new_no_eq;
}

void	remove_if_no_eq(t_shell *shell, t_export *export)
{
	int		index;
	int		len;

	index = -1;
	len = 0;
	while (shell->no_eq[len])
	{
		if (shell->no_eq[len] == export->key)
			index = len;
		len++;
	}
	if (index >= 0)
		renew_no_eq(shell, export, index, len);
}

void	finish_export_arg(t_shell *shell, t_export *export, int index)
{
	if (index == -1 && export->eq)
	{
		if (append_shell_envp(shell, export->new_line))
			return (exit_export(export, shell, 1));
	}
	else if (export->append == 0 && export->eq)
	{
		free(shell->envp[index]);
		shell->envp[index] = export->new_line;
	}
	else if (export->append)
	{
		free(export->new_line);
		export->new_line = ft_strjoin(shell->envp[index], export->value);
		if (!export->new_line)
			return (exit_export(export, shell, 1));
		export->value = NULL;
		free(shell->envp[index]);
		shell->envp[index] = export->new_line;
	}
	export->new_line = NULL;
	if (shell->no_eq && shell->no_eq[0])
		ft_printf(shell->no_eq[0]);
}
