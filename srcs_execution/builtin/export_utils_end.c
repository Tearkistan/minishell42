/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:35:31 by twatson           #+#    #+#             */
/*   Updated: 2026/04/10 14:42:20 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	includes_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	reset_exec_loop(char *cmd_arg, t_shell *shell, t_export *export)
{
	export->eq = 1;
	export->append = 0;
	alloc_key_value(cmd_arg, export, shell);
}

void	update_index(t_export *export, t_shell *shell, int index)
{
	free(shell->envp[index]);
	shell->envp[index] = export->new_line;
	export->new_line = NULL;
}
