/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:43:42 by twatson           #+#    #+#             */
/*   Updated: 2026/04/07 14:50:18 by twatson          ###   ########.fr       */
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
		if (ft_strcmp(unset->sorted_args[i], unset->sorted_args[i - 1]))
			unset->valid_count++;
		i++;
	}
	if (i == unset->valid_count)
		return (0);
	size = unset->valid_count + 1;
	free_matrix(unset->valid_args);
	unset->valid_args = (char **)malloc(sizeof(char *) * (size));
	if (!unset->valid_args)
		return (1);
	if (add_unique_to_array(unset))
		return (1);
	return (0);
}

void	rm_duplicate_args(t_unset *unset, t_shell *shell)
{
	unset->sorted_args = copy_array(unset->valid_args);
	if (!unset->sorted_args)
		exit_unset(unset, shell, 1);
	sort_args(unset);
	if (finalize_valid_args(unset))
		exit_unset(unset, shell, 1);
}

void	resize_unset_envp(t_unset *unset, t_shell *shell)
{
	int	size;

	size = shell->envp_len - unset->valid_envp_count + 1;
	unset->new_envp_len = size - 1;
	if (!unset->new_envp_len)
	{
		unset->new_envp = NULL;
		return ;
	}
	unset->new_envp = (char **)malloc(sizeof(char *) * size);
	if (!unset->new_envp)
		return (exit_unset(unset, shell, 1));
	unset->new_envp[unset->new_envp_len] = NULL;
}

void	resize_unset_no_eq(t_unset *unset, t_shell *shell)
{
	int	size;

	size = shell->no_eq_len - unset->valid_no_eq_count + 1;
	unset->new_no_eq_len = size - 1;
	if (unset->new_no_eq_len)
	{
		unset->new_no_eq = NULL;
		return ;
	}
	unset->new_no_eq = (char **)malloc(sizeof(char *) * size);
	if (!unset->new_no_eq)
		return (exit_unset(unset, shell, 1));
	unset->new_no_eq[unset->new_no_eq_len] = NULL;
}
