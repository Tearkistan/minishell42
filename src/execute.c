/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:19:50 by twatson           #+#    #+#             */
/*   Updated: 2026/01/19 13:19:24 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_heredoc_mode(t_pipex *pipex, t_redirects *redir, t_shell *sh)
{
	if (heredoc_read(redir, pipex, sh) == 1)
		return (1);
	pipex->infile = pipex->pipe_fd[0];
	pipex->prev_fd = pipex->infile;
	return (0);
}

static int	init_norm_mode(t_pipex *pipex, t_redirects *redir)
{
	if (redir->type == IN)
	{
		pipex->infile = open(redir->target, O_RDONLY);
		if (pipex->infile < 0)
			perror("norm infile");
		pipex->prev_fd = pipex->infile;
	}		
	else if (redir->type == OUT)
	{
		pipex->outfile = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex->outfile < 0)
			perror_exit("norm outfile");
	}
	else if (redir->type == APPEND)
	{
		pipex->outfile = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (pipex->outfile < 0)
			perror_exit("norm outfile");	
	}
	else
		return (perror("norm mode redir parsing error"), 1);
	return (0);
}

int	init_redirects(t_redirects *redir, t_shell *shell, t_pipex *pipex)
{
	t_redirects	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			if (init_heredoc_mode(pipex, curr, shell) == 1)
				return (1);
		}
		else
			init_norm_mode(pipex, curr);
		curr = curr->next;
	}
	return (0);
}

int	execute_cmd(t_pipeline *pipeline, t_shell *shell, t_pipex *pipex)
{
	(void)pipeline;
	(void)shell;
	(void)pipex;
	return (0);
}

static int	is_stateful(char *c)
{
	if (ft_strlen(c) >= 2 && ft_strncmp(c, "cd", 3))
		return (1);
	if (ft_strlen(c) >= 4 && ft_strncmp(c, "exit", 5))
		return (1);
	if (ft_strlen(c) >= 5 && ft_strncmp(c, "unset", 6))
		return (1);
	if (ft_strlen(c) >= 6 && ft_strncmp(c, "export", 7))
		return (1);
	return (0);
}

int execute_line(t_pipeline *pipeline, t_shell *shell)
{
	t_pipex		pipex;

	return (0); // remove to actually test excution
	pipex.last_pid = -1;
	if (!pipeline->next && is_stateful(pipeline->cmd.args[0]))
		exec_stateful_builtin(pipeline, shell, &pipex);
	else
		exec_pipeline(pipeline, shell, &pipex);
	return (0);
}
