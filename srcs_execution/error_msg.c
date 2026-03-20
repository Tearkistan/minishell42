/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:26:58 by psmolich          #+#    #+#             */
/*   Updated: 2026/03/20 16:48:14 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *message)
{
	ft_putstr_fd(Y, 2);
	ft_putstr_fd("\t", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(R, 2);
}
