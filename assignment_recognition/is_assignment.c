/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_assignment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 08:11:55 by psmolich          #+#    #+#             */
/*   Updated: 2026/04/01 08:44:14 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the input string is an assignment
// KEY=value or KEY= (i.e. empty value - "").
int	is_assignment(char *str)
{
	int	i;

	i = 0;
	if (!str || !is_valid_var_char(str[i]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!is_valid_var_char(str[i]))
			return (0);
		i++;
	}
	return (str[i] == '=');

}
