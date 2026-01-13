/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:41:17 by twatson           #+#    #+#             */
/*   Updated: 2026/01/13 17:23:09 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pipeline(t_pipeline *pipeline)
{
	(void) pipeline;
	// WIP - free pipeline of cmds - with nested arrays, strs and structs
	return ;
}

void	clean_up(t_shell *shell, t_pipeline *pipeline, char *error_msg)
{
	while (*shell->envp)
	{
		free(*shell->envp);
		shell->envp++;
	}
	free(shell->envp);
	free_pipeline(pipeline);
	if (error_msg)
		perror_exit(error_msg);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	shell_init(&shell, envp);
	shell_loop(&shell);
	clean_up(&shell, NULL, NULL);
	return (0);
}	
