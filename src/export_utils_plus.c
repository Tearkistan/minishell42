/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_plus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:21:40 by twatson           #+#    #+#             */
/*   Updated: 2026/02/16 22:47:08 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_no_eq(char *var, char **no_eq)
{
	int	i;

	i = 0;
	while (no_eq[i])
	{
		if (ft_strcmp(var, no_eq[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	add_no_equal_key(t_export *export, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->no_eq[i])
		i++;
	shell->no_eq[i] = export->key;
	i++;
	shell->no_eq[i] = NULL;
}

void	finish_export_arg(t_shell *shell, t_export *export, int index)
{
	if (index == -1)
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
}
