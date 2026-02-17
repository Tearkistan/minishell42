/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipeline_from_tokens.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:15:54 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:38:01 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*empty_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->cmd.args = NULL;
	pipeline->cmd.redirects = NULL;
	pipeline->next = NULL;
	return (pipeline);
}

t_pipeline	*create_pipeline_from_tokens(t_token *tokens, t_shell shell)
{
	t_pipeline	*head;
	t_pipeline	*current;

	head = empty_pipeline();
	if (!head)
		return (NULL);
	current = head;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			if (!add_pipe(&current))
				return (free_pipeline(head), NULL);
		}
		else if (tokens->type == TOKEN_REDIR)
		{
			if (!add_redir(current, &tokens, shell))
				return (free_pipeline(head), NULL);
		}
		else
			if (!add_arg(current, *tokens, shell))
				return (free_pipeline(head), NULL);
		tokens = tokens->next;
	}
	return (head);
}
