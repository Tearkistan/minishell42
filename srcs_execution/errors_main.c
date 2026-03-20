/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:02:18 by twatson           #+#    #+#             */
/*   Updated: 2026/03/20 16:47:52 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit(const char *label)
{
	perror(label);
	exit(1);
}

void	msg_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	ft_putendl_fd("\n", 2);
	exit(1);
}
