/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_var_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 12:09:32 by psmolich          #+#    #+#             */
/*   Updated: 2026/03/31 12:09:45 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the character is valid for variable names
// (alphanumeric or underscore).
int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
