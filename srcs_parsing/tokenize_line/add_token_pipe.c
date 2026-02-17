/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 08:51:07 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:36:46 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token_pipe(t_token **tokens)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (error_msg(ERR_MEMORY), FAILURE);
	new_token->value = NULL;
	new_token->type = TOKEN_PIPE;
	new_token->next = NULL;
	return (add_token_back(tokens, new_token));
}
