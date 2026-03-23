/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:42:59 by twatson           #+#    #+#             */
/*   Updated: 2026/03/23 17:35:45 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_exists(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (ft_isprint(*str))
			return (1);
		str++;
	}
	return (0);
}

static void	resolve_prompt_sigint(t_shell *shell)
{
	g_sig = 0;
	shell->last_status = 130;
}

static void	received_ctrld(t_shell *shell)
{
	shell->running = 0;
	clean_up(shell, NULL, NULL, "exit");
}

void	shell_loop(t_shell *shell)
{
	char		*line;
	t_pipeline	*pipeline;

	while (shell->running)
	{
		line = readline(RL_RD PROMPT RL_R);
		if (g_sig == SIGINT)
			resolve_prompt_sigint(shell);
		else if (!line)
			received_ctrld(shell);
		else if (!(line[0] == '\0' || print_exists(line) == 0))
		{
			add_history(line);
			pipeline = parse_line(line, *shell);
			if (!pipeline)
				shell->last_status = 2;
			else
				execute_line(pipeline, shell);
			free_pipeline(pipeline);
		}
		free(line);
	}
}
