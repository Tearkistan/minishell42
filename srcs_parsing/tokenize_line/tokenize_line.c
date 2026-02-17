/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:40:58 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:37:14 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_line(char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line && line[i])
	{
		if (skip_whitespaces(line, &i) == NUL)
			break ;
		if (line[i] == PIPE)
		{
			if (!add_token_pipe(&tokens))
				return (free_tokens(tokens), NULL);
			i++;
		}
		else if (is_redir(line[i]))
		{
			if (!add_token_redir(&tokens, line, &i))
				return (free_tokens(tokens), NULL);
		}
		else
			if (!add_token_word(&tokens, line, &i))
				return (free_tokens(tokens), NULL);
	}
	return (tokens);
}
