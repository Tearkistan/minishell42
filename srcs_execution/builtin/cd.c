/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:08:30 by twatson           #+#    #+#             */
/*   Updated: 2026/03/20 16:41:09 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Search "OLDPWD=" / "PWD=" respectively
if exist replace
else append 
using strncmp, strjoin, free */

static void	update_old_pwd(t_cd *cd, t_shell *shell)
{
	int	i;

	i = 0;
	if (getenv("OLDPWD"))
	{
		while (strncmp(shell->envp[i], "OLDPWD=", 7) != 0)
			i++;
		free(shell->envp[i]);
		shell->envp[i] = ft_strjoin("OLDPWD=", cd->old_pwd);
		if (!shell->envp[i])
			perror_cd("cd: memory allocation fail", cd, shell, 0);
	}
	else
		append_shell_envp(shell, cd->old_pwd);
	if (!shell->envp)
		perror_cd("cd new_envp allocation fail", cd, shell, 0);
	return ;
}

static void	update_new_pwd(t_cd *cd, t_shell *shell)
{
	int	i;

	i = 0;
	if (shell_getenv("PWD", shell))
	{
		while (strncmp(shell->envp[i], "PWD=", 4) != 0)
			i++;
		free(shell->envp[i]);
		shell->envp[i] = ft_strjoin("PWD=", cd->new_pwd);
		if (!shell->envp[i])
			perror_cd("cd: memory allocation fail", cd, shell, 0);
	}
	else
		append_shell_envp(shell, cd->new_pwd);
	if (!shell->envp)
		perror_cd("cd new_envp allocation fail", cd, shell, 0);
	return ;
}

static void	chdir_success(t_cd *cd, t_shell *shell)
{
	cd->new_pwd = getcwd(NULL, 0);
	update_old_pwd(cd, shell);
	update_new_pwd(cd, shell);
}

static void	exec_cd(char **cmd_args, t_shell *shell, t_cd *cd)
{
	char	*target;

	if (cd->arg_count > 2)
		error_msg_cd("cd: too many arguments", cd, shell, 1);
	else if (cd->arg_count == 1)
	{
		target = shell_getenv("HOME", shell);
		if (!target)
			error_msg_cd("cd: no HOME found", cd, shell, 1);
	}
	if (cd->else_error)
		return ;
	else if (cd->arg_count == 2)
		target = cmd_args[1];
	if (shell_getenv("PWD", shell))
		cd->old_pwd = ft_strdup(shell_getenv("PWD", shell));
	if (chdir(target) == 0)
	{
		chdir_success(cd, shell);
		return ;
	}
	if (!cd->else_error)
		perror_cd("cd", cd, shell, 1);
	return ;
}

int	exec_cd_ctrl(char **cmd_args, t_shell *shell, int parent)
{
	t_cd	cd;

	cd.old_pwd = NULL;
	cd.new_pwd = NULL;
	cd.else_error = 0;
	cd.path_check = -1;
	cd.arg_count = 0;
	cd.parent = parent;
	while (cmd_args[cd.arg_count])
		cd.arg_count++;
	exec_cd(cmd_args, shell, &cd);
	if (cd.old_pwd)
	{
		free(cd.old_pwd);
		cd.old_pwd = NULL;
	}
	if (cd.new_pwd)
		free(cd.new_pwd);
	return (0);
}
