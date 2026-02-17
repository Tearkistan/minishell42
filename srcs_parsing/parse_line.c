/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:40:13 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:36:01 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*parse_line(char *line, t_shell shell)
{
	t_token		*tokens;
	t_pipeline	*head;

	tokens = tokenize_line(line);
	if (!tokens)
		return (NULL);
	print_tokens(tokens); // Debug print to show the tokens after tokenization
	if (check_token_syntax(tokens) == FAILURE)
		return (free_tokens(tokens), NULL);
	head = create_pipeline_from_tokens(tokens, shell);
	if (!head)
		return (error_msg(ERR_MEMORY), free_tokens(tokens), NULL);
	return (free_tokens(tokens), head);
}
