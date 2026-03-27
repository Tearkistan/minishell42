/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:18:21 by twatson           #+#    #+#             */
/*   Updated: 2026/03/27 15:58:12 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirects	*last_in_finder(t_redirects *redir)
{
	t_redirects	*last_in;
	t_redirects	*curr;

	last_in = NULL;
	curr = redir;
	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == HEREDOC)
			last_in = curr;
		curr = curr->next;
	}
	return (last_in);
}

