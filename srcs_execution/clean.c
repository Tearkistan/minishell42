/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:43:32 by twatson           #+#    #+#             */
/*   Updated: 2026/02/22 12:14:45 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **dir)
{
	int	i;

	i = 0;
	while (dir[i] != NULL)
	{
		free(dir[i]);
		i++;
	}
	free(dir);
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
	free_matrix(shell->envp);
	i = 0;
	while (shell->no_eq[i])
	{
		free(shell->no_eq[i]);
		i++;
	}
	return ;
}

/* leveraged for ctrl-d and exit on parent (single command) call */

void	clean_up(t_shell *sh, t_pipeline *pipeline, char *line, char *err_msg)
{
	int	code;

	code = sh->last_status;
	rl_clear_history();
	if (sh->running == 0)
		free_shell(sh);
	if (pipeline)
		free_pipeline(pipeline);
	if (line) // ideally remove parameter if not used by parsing
		free(line);
	if (err_msg && ft_strncmp(err_msg, "exit", 5) == 0)
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (err_msg && ft_strncmp(err_msg, "42", 3) == 0)
		exit (code);
	else if (err_msg)
		perror_exit(err_msg);
	return ;
}
