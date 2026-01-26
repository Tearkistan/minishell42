/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_stateful.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:08:30 by twatson           #+#    #+#             */
/*   Updated: 2026/01/26 17:09:05 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(char **cmd_args, char **envp);
void	exec_exit(char **cmd_args, char **envp);
void	exec_unset(char **cmd_args, char **envp);
void	exec_export(char **cmd_args, char **envp);