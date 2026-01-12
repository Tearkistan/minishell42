/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:42:59 by twatson           #+#    #+#             */
/*   Updated: 2026/01/12 13:28:10 by twatson          ###   ########.fr       */
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

int shell_loop(char **envp)
{
	char *line;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			clean_up();
		else if (line[0] == '\0' || printable_exists(line))
		{
			free(line);
			continue ;
		}
		(void) envp;
		// add_history (if non-empty)
		// parse -> execute
		// free line + per-iteration structs
	}
	return (0);
}
