/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:42:59 by twatson           #+#    #+#             */
/*   Updated: 2026/01/14 11:35:37 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	printable_exists(char *str)
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
		else if (line[0] == '\0' || printable_exists(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		parse_line(&pipeline, line, shell);
		execute_line(&pipeline, shell);
		clean_up(NULL, &pipeline, line, NULL);
	}
	return ;
}
