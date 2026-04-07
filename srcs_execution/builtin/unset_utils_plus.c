/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:51:08 by twatson           #+#    #+#             */
/*   Updated: 2026/04/07 14:50:20 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_unique_to_array(t_unset *unset)
{
	int	i;
	int	j;

	unset->valid_args[0] = ft_strdup (unset->sorted_args[0]);
	i = 1;
	j = 1;
	while (unset->sorted_args[i])
	{
		if (ft_strcmp(unset->sorted_args[i], unset->sorted_args[i - 1]))
		{
			unset->valid_args[j] = ft_strdup(unset->sorted_args[i]);
			if (!unset->valid_args[j])
				return (1);
			j++;
		}
		i++;
	}
	unset->valid_args[j] = NULL;
	return (0);
}

void	skip_valid_args_envp(t_unset *unset, t_shell *shell)
{
	int	i;
	int	skip;

	i = 0;
	skip = 0;
	while (shell->envp && shell->envp[i + skip])
	{
		if (ft_strncmp_set(shell->envp[i + skip], unset->valid_args) == 0)
			skip++;
		unset->new_envp[i] = ft_strdup(shell->envp[i + skip]);
		if (!unset->new_envp[i])
			exit_unset(unset, shell, 1);
		i++;
	}
	free_matrix(shell->envp);
	shell->envp = unset->new_envp;
	shell->envp_len = unset->new_envp_len;
	unset->new_envp = NULL;
}

void	skip_valid_args_no_eq(t_unset *unset, t_shell *shell)
{
	int	i;
	int	skip;

	i = 0;
	skip = 0;
	while (shell->no_eq && shell->no_eq[i + skip])
	{
		if (ft_strncmp_set(shell->no_eq[i + skip], unset->valid_args) == 0)
			skip++;
		unset->new_no_eq[i] = ft_strdup(shell->no_eq[i + skip]);
		if (!unset->new_no_eq[i])
			exit_unset(unset, shell, 1);
		i++;
	}
	free_matrix(shell->no_eq);
	shell->no_eq = unset->new_no_eq;
	shell->no_eq_len = unset->new_no_eq_len;
	unset->new_no_eq = NULL;
}
