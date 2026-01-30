/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_stateful.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:08:30 by twatson           #+#    #+#             */
/*   Updated: 2026/01/30 13:48:47 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Search "OLDPWD=" / "PWD=" respectively
if exist replace
else append 
using strncmp, strjoin, free */

/* Universal start but malloc allocation / freeing heavy / incomplete freeing
static int	update_envp_line(char *envp_label, char *new_value, t_shell *shell)
{
	int	i;
	char	**new_envp;
    char    *search;

	i = 0;
	if (getenv(envp_label))
	{
		search = ft_strjoin(envp_lable, "=");
        if (!search)
            perror_exit("cd: memory allocation fail");
        while (strncmp(shell->envp[i], "OLDPWD=", 7) != 0)
        		i++;
		free(shell->envp[i]);
        shell->envp[i] = ft_strjoin("OLDPWD=", new_value);
		if (!shell->envp[i])
			perror_exit("cd: memory allocation fail");
	}
	if (shell->envp[i] != NULL)
	{   
		while (shell->envp[i] != NULL)
			i++;
        new_envp = append_shell_envp(shell, i, new_value);
		if (!new_envp)
			perror_exit("cd new_envp allocation fail");
	}
	return (0);
}*/

static int	update_old_pwd(char *old_pwd, t_shell *shell)
{
	int	i;
	char	**new_envp;

	i = 0;
	if (getenv("OLDPWD"))
	{
		while (strncmp(shell->envp[i], "OLDPWD=", 7) != 0)
        		i++;
		free(shell->envp[i]);
        shell->envp[i] = ft_strjoin("OLDPWD=", old_pwd);
		if (!shell->envp[i])
			perror_exit("cd: memory allocation fail");
	}
	if (shell->envp[i] != NULL)
	{   
		while (shell->envp[i] != NULL)
			i++;
        new_envp = append_shell_envp(shell, i, old_pwd);
		if (!new_envp)
			perror_exit("cd new_envp allocation fail");
	}
	return (0);
}

static int	update_new_pwd(char *new_pwd, t_shell *shell)
{
	int	i;
	char	**new_envp;

	i = 0;
	if (getenv("PWD"))
	{
		while (strncmp(shell->envp[i], "PWD=", 7) != 0)
        		i++;
		free(shell->envp[i]);
        shell->envp[i] = ft_strjoin("PWD=", new_pwd);
		if (!shell->envp[i])
			perror_exit("cd: memory allocation fail");
	}
	if (shell->envp[i] != NULL)
	{   
		while (shell->envp[i] != NULL)
			i++;
        new_envp = append_shell_envp(shell, i, new_pwd);
		if (!new_envp)
			perror_exit("cd new_envp allocation fail");
	}
	return (0);
}

int	exec_cd(t_pipe *pipex, char **cmd_args, t_shell *shell)
{
	char    *target;
	char    *old_pwd;
	char    *new_pwd;

	if (pipex->cmd_count > 2)
		return (perror_int("cd: too many arguments", 1));
	else if (pipex->cmd_count == 1)
	{
		if (!(target = getenv("HOME")))
			return (perror_int("cd: no HOME found", 1));
	}
	else if (pipex->cmd_count == 2)
		target = cmd_args[1];
	if (getenv("PWD"))
        	old_pwd = ft_strdup(getenv("PWD"));
	if (chdir(target) == -1)
	{
		free(old_pwd);
		return (perror_int("cd", 1));
	}
	new_pwd = getcwd(NULL, 0);
	if (update_old_pwd(old_pwd, shell))
		return (1);
	if (update_new_pwd(new_pwd, shell))
		return (1);
	return (0);
}

int	exec_exit(char **cmd_args, char **envp)
{
	(void)cmd_args;
	(void)envp;
	return (0);
}

int	exec_unset(char **cmd_args, char **envp)
{
	(void)cmd_args;
	(void)envp;
	return (0);
}

int	exec_export(char **cmd_args, char **envp)
{
	(void)cmd_args;
	(void)envp;
	return (0);
}
