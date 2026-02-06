/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:23:44 by twatson           #+#    #+#             */
/*   Updated: 2026/01/19 14:23:56 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* exits shell if exit as single command */

int	exec_stateful_builtin(t_pipeline *pline, t_shell *sh, t_pipe *pipex)
{
    (void)pipex;
	set_signals_parent_running();
	builtin_exec(pline->cmd.args, sh, 1);
	if (ft_strncmp(pline->cmd.args[0], "exit", 5) == 0)
		sh->running = 0;
	return (0);
}