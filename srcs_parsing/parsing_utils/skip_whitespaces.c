/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 09:26:45 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:37:46 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Updates the index to point to the first non-whitespace character.
// Returns the character at the new index.
char	skip_whitespaces(char *line, int *index)
{
	while (line[*index] && ft_isspace(line[*index]))
		(*index)++;
	return (line[*index]);
}
