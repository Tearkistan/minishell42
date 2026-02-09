/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
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
	char	*old_temp;
	char	*new_temp;
	int		arg_count;
	int		parent;
}	t_unset;

static void	exec_unset(char **cmd_args, t_shell *shell, t_unset *unset)
{
	(void)cmd_args;
	(void)shell;
	(void)unset;
}

int	exec_unset_ctrl(char **cmd_args, t_shell *shell, int parent)
{
    t_unset	unset;

	unset.old_temp = NULL;
	unset.new_temp = NULL;
	unset.arg_count = 0;
	unset.parent = parent;
	while (cmd_args[unset.arg_count])
		unset.arg_count++;
	if (unset.arg_count == 1)
		return (0);
	exec_unset(cmd_args, shell, &unset);
	(void)cmd_args;
	(void)shell;
	(void)parent;
	return (0);
}
