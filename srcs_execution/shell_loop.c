/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:42:59 by twatson           #+#    #+#             */
/*   Updated: 2026/03/23 13:53:31 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RL_RD "\001\033[91m\002"
#define RL_R "\001\033[0m\002"

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
		set_signals_prompt_mode();
		line = readline(RL_RD PROMPT RL_R);
		if (g_sig == SIGINT)
		{
			if (line)
				free(line);
			resolve_prompt_sigint(shell);
			continue ;
		}
		if (!line)
		{
			received_ctrld(shell);
			continue ;
		}
		if (line[0] == '\0' || print_exists(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		pipeline = parse_line(line, *shell);
		free(line);
		if (!pipeline)
			shell->last_status = 2;
		else
			execute_line(pipeline, shell);
		free_pipeline(pipeline);
	}
}
