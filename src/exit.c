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

int	exec_exit(char **cmd_args, t_shell *shell)
{
	int	arg_count;

	ft_printf("exit\n");
	arg_count = 0;
	while (cmd_args[arg_count] != NULL)
		arg_count++;
	if (arg_count == 1)
		exit(shell->last_status);
	else if (arg_count == 2 && ft_isalldigits(cmd_args[1]))
		exit(ft_atoi(cmd_args[1]));
	else if (ft_isalldigits(cmd_args[1]) == 0)
	{
		perror("exit: numeric argument required");
		exit(2);
	}
	else if (arg_count > 2)
	{
		perror("exit: too many arguments");
		shell->last_status = 1;
	}
	return (0);
}
