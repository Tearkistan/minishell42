/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:01:36 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 14:33:49 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SUCCESS 1
#define FAILURE 0

// do not output the trailing newline
// -n or -nnnnnn... are valid options
static int	exec_echo_n_opion(char *arg)
{
	int	i;

	if (!arg)
		return (FALSE);
	if (arg[0] != '-')
		return (FALSE);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

// echo - display a line of text
int	exec_echo(char **cmd_args, char **envp)
{
	int	i;
	int	newline;

	(void)envp;
	if (!cmd_args)
		return (FAILURE); // should not happen, but just in case
	if (cmd_args[0] == NULL || ft_strcmp(cmd_args[0], "echo") != 0)
		return (ft_printf("not the echo command"), FAILURE); // not the echo command
	if (!cmd_args[1])
		return (ft_putstr_fd("\n", STDOUT_FILENO), SUCCESS); // echo with no arguments should print a newline
	newline = TRUE;
	i = 1;
	while (exec_echo_n_opion(cmd_args[i])) // check for -n options
	{
		newline = FALSE;
		i++;
	}
	while (cmd_args[i])
	{
		ft_putstr_fd(cmd_args[i++], STDOUT_FILENO);
		if (cmd_args[i]) // print space if not the last argument
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (newline)
			ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
