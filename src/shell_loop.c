/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:42:59 by twatson           #+#    #+#             */
/*   Updated: 2026/01/16 18:35:16 by twatson          ###   ########.fr       */
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

void shell_loop(t_shell *shell)
{
	char		*line;
	t_pipeline	pipeline;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			clean_up(shell, NULL, NULL, "exit");
		else if (line[0] == '\0' || print_exists(line) == 0 || g_sig == SIGINT)
		{
			free(line);
			if (g_sig == SIGINT)
				resolve_prompt_sigint(shell);
			continue ;
		}
		add_history(line);
		if (parse_line(&pipeline, line, shell) == 0)
			execute_line(&pipeline, shell);
		clean_up(NULL, &pipeline, line, NULL);
	}
	return ;
}
