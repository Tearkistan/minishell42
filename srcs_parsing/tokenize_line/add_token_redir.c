/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 08:49:56 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:36:51 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*redir_token_value(char *line, int *index)
{
	char	*value;

	if (line[*index] == '>' && line[*index + 1] == '>')
	{
		value = ft_strdup(">>");
		*index += 2;
	}
	else if (line[*index] == '<' && line[*index + 1] == '<')
	{
		value = ft_strdup("<<");
		*index += 2;
	}
	else
	{
		value = char_to_str(line[*index]);
		(*index)++;
	}
	return (value);
}

int	add_token_redir(t_token **tokens, char *line, int *index)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (error_msg(ERR_MEMORY), FAILURE);
	new_token->value = redir_token_value(line, index);
	if (!new_token->value)
		return (error_msg(ERR_MEMORY), free(new_token), FAILURE);
	new_token->type = TOKEN_REDIR;
	new_token->next = NULL;
	return (add_token_back(tokens, new_token));
}
