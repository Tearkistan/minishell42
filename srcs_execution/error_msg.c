/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:26:58 by psmolich          #+#    #+#             */
/*   Updated: 2026/03/23 08:35:26 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *message, char *input)
{
	ft_putstr_fd(Y, 2);
	while (*message && *message != '@')
		ft_putchar_fd(*message++, 2);
	if (*message == '@')
	{
		ft_putstr_fd(input, 2);
		message++;
	}
	while (*message)
		ft_putchar_fd(*message++, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(R, 2);
}
