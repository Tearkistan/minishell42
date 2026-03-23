/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:57:45 by psmolich          #+#    #+#             */
/*   Updated: 2026/03/23 08:58:52 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Syntax error: PIPE cannot be first
static int	first_pipe(t_token *tokens)
{
	if (tokens->type == TOKEN_PIPE)
	{
		error_msg(ERR_UNEXPECTED_TOKEN, "|");
		return (TRUE);
	}
	return (FALSE);
}

static int	pipe_followed_by_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			if (!tokens->next || tokens->next->type == TOKEN_PIPE)
			{
				error_msg(ERR_UNEXPECTED_TOKEN, "|");
				return (TRUE);
			}
		}
		tokens = tokens->next;
	}
	return (FALSE);
}

// Syntax error: REDIR must be followed by a WORD
static int	redir_not_followed_by_word(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_REDIR)
		{
			if (!tokens->next)
			{
				error_msg(ERR_UNEXPECTED_TOKEN, "newline");
				return (TRUE);
			}
			else if (tokens->next->type != TOKEN_WORD)
			{
				error_msg(ERR_UNEXPECTED_TOKEN, tokens->next->value);
				return (TRUE);
			}
		}
		tokens = tokens->next;
	}
	return (FALSE);
}

// Syntax error: WORD token must have a non-empty value
static int	word_without_value(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD && (!tokens->value))
		{
			error_msg(ERR_EMPTY_WORD, NULL);
			return (TRUE);
		}
		tokens = tokens->next;
	}
	return (FALSE);
}

int	check_token_syntax(t_token *tokens)
{
	if (first_pipe(tokens)
		|| pipe_followed_by_pipe(tokens)
		|| redir_not_followed_by_word(tokens)
		|| word_without_value(tokens))
		return (FAILURE);
	return (SUCCESS);
}
