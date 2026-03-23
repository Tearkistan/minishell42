/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:56:12 by twatson           #+#    #+#             */
/*   Updated: 2026/03/23 08:03:06 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg_cd(char *err_msg, t_cd *cd, t_shell *shell, int running)
{
	if (cd->old_pwd)
	{
		free(cd->old_pwd);
		cd->old_pwd = NULL;
	}
	if (cd->new_pwd)
		free(cd->new_pwd);
	if (!cd->else_error)
	{
		error_msg(err_msg);
		cd->else_error = 1;
	}
	if (cd->parent)
	{
		shell->running = running;
		shell->last_status = 1;
	}
	else
		exit(1);
}

void	perror_cd(char *error_msg, t_cd *cd, t_shell *shell, int running)
{
	if (cd->old_pwd)
	{
		free(cd->old_pwd);
		cd->old_pwd = NULL;
	}
	if (cd->new_pwd)
		free(cd->new_pwd);
	if (!cd->else_error)
	{
		perror(error_msg);
		cd->else_error = 1;
	}
	if (cd->parent)
	{
		shell->running = running;
		shell->last_status = 1;
	}
	else
		exit(1);
}
