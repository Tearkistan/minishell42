/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:24:43 by twatson           #+#    #+#             */
/*   Updated: 2026/01/19 15:21:38 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipeline(t_pipeline *pipeline, t_shell *shell, t_pipex *pipex)
{
	/* still needs to be refactor for updated pipeline order */
	t_pipeline *curr;

	curr = pipeline;
	set_signals_parent_running();
	while (curr)
	{
		if (init_redirects(&curr->cmd.redirects, shell, pipex) == 1)
			return (0);
		execute_cmd(curr, shell, pipex);
		curr = curr->next;
	}
	return (0);
}
