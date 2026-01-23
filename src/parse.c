// #include "minishell.h"

// int	parse_line(t_pipeline *pipeline, char *line, t_shell *shell)
// {
// 	(void) pipeline;
// 	(void) line;
// 	(void) shell; /* read-only purpose to expand environment variables */
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:31:32 by psmolich          #+#    #+#             */
/*   Updated: 2026/01/23 09:50:40 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(char c)
{
	ft_printf("MINIsHELL: syntax error near unexpected token `%c'\n", c);
	return (1);
}

int	parse_line(t_pipeline *pipeline, char *line, t_shell *shell)
{
	t_token	token;

	((void)shell, (void)pipeline);
	token = tokenize(line);
	return (0);
}



