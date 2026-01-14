/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:41:17 by twatson           #+#    #+#             */
/*   Updated: 2026/01/14 12:45:29 by twatson          ###   ########.fr       */
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

void	clean_up(t_shell *shell, t_pipeline *pipeline, char *error_msg)
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
	else if (error_msg)
		perror_exit(error_msg);
	return ;
}

/* static void	print_shell_envp(t_shell *shell) // comment out for main branch - for visual testing only
{
	int i;

	i = 0;
	while (shell->envp[i])
		printf("%s\n", shell->envp[i++]);
	return ;
} */

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	shell_init(&shell, envp);
	// print_shell_envp(&shell); // comment out for main branch - visual testing only
	shell_loop(&shell);
	clean_up(&shell, NULL, NULL);
	return (0);
}	
