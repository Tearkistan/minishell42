/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:26:58 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/22 13:00:55 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *message)
{
	ft_putstr_fd(Y, 2);
	ft_putstr_fd("\t", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(R, 2);
}
