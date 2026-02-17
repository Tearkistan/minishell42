/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 08:52:17 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:36:59 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_quoted_word(char *line, int *index, char quote_type,
	int *unclosed_quote)
{
	int		start;
	char	*word;

	start = *index;
	(*index)++;
	while (line[*index] && line[*index] != quote_type)
		(*index)++;
	if (line[*index] == NUL)
	{
		*unclosed_quote = TRUE;
		return (NULL);
	}
	(*index)++;
	word = ft_substr(line, start, *index - start);
	return (word);
}

static char	*word_token_value(char *line, int *index)
{
	char	*value;
	char	*temp;
	int		unclosed_quote;

	unclosed_quote = FALSE;
	value = ft_strdup("");
	if (!value)
		return (error_msg(ERR_MEMORY), NULL);
	while (line[*index] && !ft_isspace(line[*index])
		&& !is_special(line[*index]))
	{
		if (line[*index] == SQ || line[*index] == DQ)
			temp = get_quoted_word(line, index, line[*index], &unclosed_quote);
		else
			temp = char_to_str(line[(*index)++]);
		if (unclosed_quote)
			return (error_msg(ERR_UNCLOSED_QUOTE), free(value), NULL);
		if (!temp)
			return (error_msg(ERR_MEMORY), free(value), NULL);
		value = ft_strjoin_free(value, temp);
		if (!value)
			return (error_msg(ERR_MEMORY), NULL);
	}
	return (value);
}

int	add_token_word(t_token **tokens, char *line, int *index)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (error_msg(ERR_MEMORY), FAILURE);
	new_token->value = word_token_value(line, index);
	if (!new_token->value)
		return (free(new_token), FAILURE);
	new_token->type = TOKEN_WORD;
	new_token->next = NULL;
	return (add_token_back(tokens, new_token));
}
