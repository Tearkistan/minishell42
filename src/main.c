/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:41:17 by twatson           #+#    #+#             */
/*   Updated: 2026/01/23 11:51:48 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_shell_envp(t_shell *shell) // comment out for main branch - for visual testing only
// {
// 	int i;

// 	i = 0;
// 	while (shell->envp[i])
// 		printf("%s\n", shell->envp[i++]);
// 	return ;
// }

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	shell_init(&shell, envp);
	// print_shell_envp(&shell); // comment out for main branch - visual testing only
	shell_loop(&shell);
	clean_up(&shell, NULL, NULL, NULL);
	return (0);
}
