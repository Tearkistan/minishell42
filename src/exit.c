/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:35:30 by twatson           #+#    #+#             */
/*   Updated: 2026/02/02 16:36:14 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if 1st argument cmd_args[1] determines if cmd_args > 2 returns must be numeric 
or too many arguments error when. When exit occurs in parent, actually exits shell, 
else only exits the child */

static int	numeric_check(char *code)
{
	int	check;

	check = 0;
	if (code[check] == '-' || code[check] == '+')
		check++;
	while (code[check] != '\0')
	{
		if (ft_isdigit(code[check]) == 0)
			return (0);
		check++;
	}
	return (1);
}

static void exit_check(t_shell *shell, int code, int parent)
{
	if (parent)
	{
		shell->last_status = code;
		shell->running = 0;
	}
	else
		exit(code);
	return ;
}

int	exec_exit(char **cmd_args, t_shell *shell, int parent)
{
	int	arg_count;
	int	given;

	ft_printf("exit\n");
	arg_count = 0;
	while (cmd_args[arg_count] != NULL)
		arg_count++;
	if (arg_count == 1)
		exit_check(shell, shell->last_status, parent);
	else if (arg_count == 2 && numeric_check(cmd_args[1]))
	{
		given = ft_atoi(cmd_args[1]);
		exit_check(shell, given, parent);
	}
	else if (numeric_check(cmd_args[1]) == 0)
	{
		perror("exit: numeric argument required");
		exit_check(shell, 2, 1);
	}
	else if (arg_count > 2)
	{
		perror("exit: too many arguments");
		shell->last_status = 1;
	}
	return (0);
}
