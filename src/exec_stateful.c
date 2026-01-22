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

int	exec_stateful_builtin(t_pipeline *pline, t_shell *sh, t_pipe *pipex)
{
	/* still needs to be refactor for updated pipeline order */
    set_signals_parent_running();
	(void)pipex;
	exec_cmd(pline->cmd.args, sh->envp);
	return (0);
}