/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:36:30 by twatson           #+#    #+#             */
/*   Updated: 2026/02/02 16:37:02 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* removes one or more environment variables. Must start with letter or '_' and
otherwise can only include digits. if any argument is invalid in composition return 1.
No argument or arguments not exist leads to no change but also no error,  */

typedef struct	s_unset
{
	char	**new_envp;
	char	**valid_args;
	int		arg_count;
	int		valid_count;
	int		parent;
	int		exit;
}	t_unset;

static void	exit_unset(t_unset *unset, t_shell *shell, int alloc_fail)
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

static int	unset_arg_error(char *cmd_args)
{
	int	i;

	i = 0;
	if (cmd_args[i] != '_' || !(ft_isalpha(cmd_args[i])))
		return (1);
	i++;
	while (cmd_args[i])
	{
		if (cmd_args[i] != '_' || !(ft_isalnum(cmd_args[i])))
			return (1);
		i++;
	}
	return (0);
}

static void remove_valid_args(char **cmd_args, t_shell *shell, t_unset *unset)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd_args[i])
	{
		if (getenv(cmd_args[i]))
		{
			unset->valid_args[j] = cmd_args[i];
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (shell->envp[i])
	{
		while (ft_strncmp_set(shell->envp[i + j], unset->valid_args) == 0)
			j++;
		unset->new_envp[i] = shell->envp[i + j];
		i++;
	}
	free_matrix(shell->envp);
	shell->envp = unset->new_envp;
	return ;
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
	if (unset->valid_count == 0 && unset->exit == 0)
		return ;
	size = shell->envp_len - unset->valid_count + 1;
	unset->new_envp = (char **)malloc(sizeof(char *) * size);
	if (!unset->new_envp)
		exit_unset(unset, shell, 1);
	size = unset->valid_count + 1;
	unset->valid_args = (char **)malloc(sizeof(char *) * size);
	if (!unset->valid_args)
		exit_unset(unset, shell, 1);
	remove_valid_args(cmd_args, shell, unset);
}

int	exec_unset_ctrl(char **cmd_args, t_shell *shell, int parent)
{
    t_unset	unset;

	unset.new_envp= NULL;
	unset.valid_args = NULL;
	unset.arg_count = 0;
	unset.valid_count = 0;
	unset.parent = parent;
	unset.exit = 0;
	while (cmd_args[unset.arg_count])
		unset.arg_count++;
	if (unset.arg_count == 1)
		return (0);
	exec_unset(cmd_args, shell, &unset);
	if (unset.new_envp)
		free(unset.new_envp);
	if (unset.valid_args)
		free(unset.valid_args);
	return (0);
}
