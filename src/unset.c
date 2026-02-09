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
	int		env_count;
	int		parent;
	int		exit;
}	t_unset;

static void	exit_unset(t_unset *unset, t_shell *shell)
{
	if (unset->new_envp)
		free(unset->new_envp);
	if (unset->valid_args)
		free(unset->valid_args);
	if (unset->parent)
	{
		shell->running = 0;
		shell->last_status = 1;
	}
	else
		exit(1);
}

static int arg_check_unset(char **cmd_args, t_shell *shell, t_unset unset)
{
	int	i;

	i = 1;
	while (cmd_args[i])
	{
		if (arg_error(cmd_args[i]))
			unset->exit = 1;
		if (getenv(cmd_args[i]))
			unset->valid_count++;
	}
}

static void	exec_unset(char **cmd_args, t_shell *shell, t_unset *unset)
{
	int	size;

	arg_check_unset(cmd_args, shell, unset);
	if (unset->valid_count = 0 && unset->exit = 0);
		return ;
	size = unset->env_count - unset->valid_args + 1;
	unset->new_envp = (char **)malloc(sizeof(char *) * size);
	if (unset->exit)
		exit_unset(unset, shell);
	(void)cmd_args;
	(void)shell;
	(void)unset;
}

int	exec_unset_ctrl(char **cmd_args, t_shell *shell, int parent)
{
    t_unset	unset;

	unset.new_envp= NULL;
	unset.valid_args = NULL;
	unset.env_count = 0;
	unset.arg_count = 0;
	unset.valid_count = 0;
	unset.parent = parent;
	unset.exit = 0;
	while (shell->envp[unset->env_count])
		env_count;
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
