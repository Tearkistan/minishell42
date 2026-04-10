/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:45:45 by psmolich          #+#    #+#             */
/*   Updated: 2026/04/10 12:46:30 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline_size(t_pipeline *p)
{
	int			i;
	t_pipeline	*curr;

	curr = p;
	i = 0;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
