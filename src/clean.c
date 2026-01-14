/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:43:32 by twatson           #+#    #+#             */
/*   Updated: 2026/01/14 13:43:38 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pipeline(t_pipeline *pipeline)
{
	(void) pipeline;
	// WIP - free pipeline of cmds - with nested arrays, strs and structs
	return ;
}

static void free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		free(shell->envp[i]);
		i++;
	}
	free(shell->envp);
	return ;
}

void	clean_up(t_shell *shell, t_pipeline *pipeline, char *line, char *error_msg)
{
	if (shell)
		free_shell(shell);
	if (pipeline)
		free_pipeline(pipeline);
	if (ft_strncmp(error_msg, "exit", 5) == 0)
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (line)
		free(line);
	else if (error_msg)
		perror_exit(error_msg);
	return ;
}
