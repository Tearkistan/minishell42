/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:19:50 by twatson           #+#    #+#             */
/*   Updated: 2026/01/15 15:56:23 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_redirects(t_redirects *redir, t_shell *shell, t_pipex *pipex)
{
	t_redirects	*curr;

	curr = redir
	while (curr)
	{
		if (curr->type == HEREDOC)
			init_heredoc_mode(pipex, redir);
		else
			init_norm_mode(pipex, redir);
		curr = curr->next;
	}
	return (0);
}

int execute_line(t_pipeline *pipeline, t_shell *shell)
{
	t_pipex		pipex;
	t_pipeline	*curr;
	
	curr = pipeline
	while (curr)
	{
		init_redirects(curr->cmd->redirects, shell, &pipex);
		curr = curr->next;
	}
	return (0);
}
