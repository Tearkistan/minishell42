/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:48:42 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:36:33 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return (FAILURE);
	if (!*tokens)
	{
		*tokens = new_token;
		return (SUCCESS);
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (SUCCESS);
}
