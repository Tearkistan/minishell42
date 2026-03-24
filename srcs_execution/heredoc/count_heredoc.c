/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 06:00:39 by psmolich          #+#    #+#             */
/*   Updated: 2026/03/24 06:00:56 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_heredoc(t_redirects *redir)
{
	int			count;
	t_redirects	*curr;

	curr = redir;
	count = 0;
	while (curr)
	{
		if (curr->type == HEREDOC)
			count++;
		curr = curr->next;
	}
	return (count);
}
