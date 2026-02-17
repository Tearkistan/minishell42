/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:02:18 by twatson           #+#    #+#             */
/*   Updated: 2026/02/17 13:57:17 by psmolich         ###   ########.fr       */
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
	exit(1);
}
