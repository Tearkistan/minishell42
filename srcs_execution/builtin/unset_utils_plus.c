/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:51:08 by twatson           #+#    #+#             */
/*   Updated: 2026/03/18 20:13:05 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_unique_to_array(t_unset *unset)
{
	int	i;
	int	j;

	unset->valid_args[0] = unset->sorted_args[0];
	i = 1;
	j = 1;
	while (unset->sorted_args[i])
	{
		if (unset->sorted_args[i] != unset->sorted_args[i - 1])
		{
			unset->valid_args[j] = unset->sorted_args[i];
			j++;
		}
		i++;
	}
}
