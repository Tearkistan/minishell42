/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buiitin_nonstateful.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:09:23 by twatson           #+#    #+#             */
/*   Updated: 2026/01/26 17:09:37 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(char **cmd_args, char **envp)
{
    (void)cmd_args;
    (void)envp;
    return (0);
}

int	exec_envp(char **cmd_args, char **envp)
{
    (void)cmd_args;
    (void)envp;
    return (0);
}

int	exec_echo(char **cmd_args, char **envp)
{
    (void)cmd_args;
    (void)envp;
    return (0);
}
