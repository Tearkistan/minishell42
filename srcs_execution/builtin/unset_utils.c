/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:43:42 by twatson           #+#    #+#             */
/*   Updated: 2026/03/18 20:16:57 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_args(t_unset *unset)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < unset->valid_count)
	{
		j = 0;
		while (j < (unset->valid_count - i - 1))
		{
			if (ft_strcmp(unset->sorted_args[j], unset->sorted_args[j + 1]) > 0)
			{
				temp = unset->sorted_args[j + 1];
				unset->sorted_args[j + 1] = unset->sorted_args[j];
				unset->sorted_args[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static int	finalize_valid_args(t_unset *unset)
{
	int	i;
	int	size;

	i = 1;
	unset->valid_count = 1;
	while (unset->sorted_args[i])
	{
		if (unset->sorted_args[i] != unset->sorted_args[i - 1])
			unset->valid_count++;
		i++;
	}
	if (i == unset->valid_count)
		return (1);
	size = unset->valid_count + 1;
	free(unset->valid_args);
	unset->valid_args = (char **)malloc(sizeof(char *) * (size));
	if (!unset->valid_args)
		return (0);
	add_unique_to_array(unset);
	return (1);
}

void	resize_unset_envp(t_unset *unset, t_shell *shell)
{
	int	size;

	size = shell->envp_len - unset->valid_count + 1;
	unset->new_envp = (char **)malloc(sizeof(char *) * size);
	if (!unset->new_envp)
		return (exit_unset(unset, shell, 1));
	unset->new_len = size - 1;
	unset->new_envp[unset->new_len] = NULL;
}

void	rm_duplicate_args(t_unset *unset, t_shell *shell)
{
	unset->sorted_args = copy_array(unset->valid_args);
	if (!unset->sorted_args)
		exit_unset(unset, shell, 1);
	sort_args(unset);
	if (!finalize_valid_args(unset))
		exit_unset(unset, shell, 1);
}

void	remove_valid_args(char **cmd_args, t_shell *shell, t_unset *unset)
{
	int	i;
	int	skip;

	get_valid_args(cmd_args, unset, shell);
	rm_duplicate_args(unset, shell);
	i = 0;
	skip = 0;
	while (shell->envp[i + skip])
	{
		if (ft_strncmp_set(shell->envp[i + skip], unset->valid_args) == 0)
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