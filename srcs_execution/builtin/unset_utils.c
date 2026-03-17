/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:43:42 by twatson           #+#    #+#             */
/*   Updated: 2026/03/17 18:26:39 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_valid_args(char **cmd_args, t_shell *shell, t_unset *unset)
{
	int	i;
	int	skip;

	get_valid_args(cmd_args, unset);
	i = 0;
	skip = 0;
	while (shell->envp[i + skip])
	{
		if (ft_strcmp_set(shell->envp[i + skip], unset->valid_args) == 0)
		{
			skip++;
			continue ;
		}
		unset->new_envp[i] = ft_strdup(shell->envp[i + skip]);
		if (!unset->new_envp[i])
			exit_unset(unset, shell, 1);
		i++;
	}
	free_matrix(shell->envp);
	shell->envp = unset->new_envp;
	shell->envp_len = unset->new_len; 
	unset->new_envp = NULL;
}

/* UNNECESSARY UPDATE ? 

void	remove_valid_args(t_shell *shell, t_unset *unset)
{
	int	i;
	int	j;
	int	skip;

	i = 0;
	skip = 0;
	while (shell->envp[i + skip])
	{
		j = 0;
		while (unset->valid_args[j])
		{
			if (ft_strcmp_set(shell->envp[i + j], unset->valid_args) == 0)
			{
				skip++;
				continue ;
			}
			j++;
		}
		unset->new_envp[i] = ft_strdup(shell->envp[i + skip]);
		if (!unset->new_envp[i])
			exit_unset(unset, shell, 1);
		i++;
	}
	unset->new_envp[i] = NULL;
	clean_unset(shell, unset);
}*/