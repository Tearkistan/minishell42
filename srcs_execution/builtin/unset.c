/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:36:30 by twatson           #+#    #+#             */
/*   Updated: 2026/03/19 12:33:23 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* removes one or more environment variables. Must start with letter or '_' and
otherwise can only include digits. if any argument is invalid in composition return 1.
No argument or arguments not exist leads to no change but also no error,  */

void	exit_unset(t_unset *unset, t_shell *shell, int alloc_fail)
{
	if (unset->new_envp)
		free_matrix(unset->new_envp);
	if (unset->valid_args)
		free_matrix(unset->valid_args);
	if (unset->parent && alloc_fail)
	{
		shell->running = 0;
		shell->last_status = 1;
	}
	else if (alloc_fail)
		exit(1);
}

static int	unset_arg_error(char *cmd_arg)
{
	int	i;

	i = 0;
	if (cmd_arg[i] != '_' || !(ft_isalpha(cmd_arg[i])))
		return (1);
	i++;
	while (cmd_arg[i])
	{
		if (cmd_arg[i] != '_' || !(ft_isalnum(cmd_arg[i])))
			return (1);
		i++;
	}
	return (0);
}

void	get_valid_args(char **cmd_args, t_unset *unset, t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd_args[i])
	{
		if (getenv(cmd_args[i]))
		{
			unset->valid_args[j] = ft_strdup(cmd_args[i]);
			if (!unset->valid_args[j])
				exit_unset(unset, shell, 1);
			j++;
		}
		i++;
	}
	unset->valid_args[j] = NULL;
}

static void	exec_unset(char **cmd_args, t_shell *shell, t_unset *unset)
{
	int	size;
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		if (unset_arg_error(cmd_args[i]))
			shell->last_status = 1;
		if (getenv(cmd_args[i]))
			unset->valid_count++;
		i++;
	}
	if (unset->valid_count == 0)
		return ;
	size = unset->valid_count + 1;
	unset->valid_args = (char **)malloc(sizeof(char *) * size);
	if (!unset->valid_args)
		return (exit_unset(unset, shell, 1));
	get_valid_args(cmd_args, unset, shell);
	rm_duplicate_args(unset, shell);
	remove_valid_args(shell, unset);
}

int	exec_unset_ctrl(char **cmd_args, t_shell *shell, int parent)
{
	t_unset	unset;

	unset.new_envp = NULL;
	unset.new_len = 0;
	unset.valid_args = NULL;
	unset.sorted_args = NULL;
	unset.arg_count = 0;
	unset.valid_count = 0;
	unset.parent = parent;
	while (cmd_args[unset.arg_count])
		unset.arg_count++;
	if (unset.arg_count == 1)
		return (0);
	exec_unset(cmd_args, shell, &unset);
	if (unset.new_envp)
		free_matrix(unset.new_envp);
	if (unset.valid_args)
		free_matrix(unset.valid_args);
	if (unset.sorted_args)
		free_matrix(unset.sorted_args);
	return (0);
}
