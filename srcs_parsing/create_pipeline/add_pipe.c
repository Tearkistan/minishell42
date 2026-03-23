/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:21:35 by psmolich          #+#    #+#             */
/*   Updated: 2026/03/23 08:55:08 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_pipe(t_pipeline **current)
{
	if (!current)
		return (FAILURE);
	(*current)->next = empty_pipeline();
	if (!(*current)->next)
		return (error_msg(ERR_MEMORY, NULL), FAILURE);
	*current = (*current)->next;
	return (SUCCESS);
}
