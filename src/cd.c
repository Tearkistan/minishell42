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

typedef struct	s_cd
{
	char	*old_pwd;
	char	*new_pwd;
	int		cmd_count;
}	t_cd;

static int	perror_cd(char *error_msg, t_cd *cd, t_shell *shell, int running)
{
	if (cd->old_pwd)
		free(cd->old_pwd);
	if (cd->new_pwd)
		free(cd->new_pwd);
	perror(error_msg);
	shell->running = running;
	return (1);
}

static int	update_old_pwd(t_cd *cd, t_shell *shell)
{
	int	i;
	char	**new_envp;

	i = 0;
	new_envp = NULL;
	if (getenv("OLDPWD"))
	{
		while (strncmp(shell->envp[i], "OLDPWD=", 7) != 0)
        		i++;
		free(shell->envp[i]);
        shell->envp[i] = ft_strjoin("OLDPWD=", cd->old_pwd);
		if (!shell->envp[i])
			perror_cd("cd: memory allocation fail", cd, shell, 0);
	}
	if (shell->envp[i] != NULL)
	{   
		while (shell->envp[i] != NULL)
			i++;
        append_shell_envp(shell, i, cd->old_pwd, new_envp);
		if (!new_envp)
			return (perror_cd("cd new_envp allocation fail", cd, shell, 0));
	}
	return (0);
}

static int	update_new_pwd(t_cd *cd, t_shell *shell)
{
	int	i;
	char	**new_envp;

	i = 0;
	new_envp = NULL;
	if (getenv("PWD"))
	{
		while (strncmp(shell->envp[i], "PWD=", 4) != 0)
        		i++;
		free(shell->envp[i]);
        shell->envp[i] = ft_strjoin("PWD=", cd->new_pwd);
		if (!shell->envp[i])
			return(perror_cd("cd: memory allocation fail", cd, shell, 0));
	}
	if (shell->envp[i] != NULL)
	{   
		while (shell->envp[i] != NULL)
			i++;
        append_shell_envp(shell, i, cd->new_pwd, new_envp);
		if (!new_envp)
			return(perror_cd("cd new_envp allocation fail", cd, shell, 0));
	}
	return (0);
}

static int	exec_cd(char **cmd_args, t_shell *shell, t_cd *cd)
{
	char    *target;

	if (cd->cmd_count > 2)
		return (perror_cd("cd: too many arguments", cd, shell, 1));
	else if (cd->cmd_count == 1)
	{
		if (!(target = getenv("HOME")))
			return (perror_cd("cd: no HOME found", cd, shell, 1));
	}
	else if (cd->cmd_count == 2)
		target = cmd_args[1];
	if (getenv("PWD"))
        	cd->old_pwd = ft_strdup(getenv("PWD"));
	if (chdir(target) == -1)
		return (perror_cd("cd", cd, shell, 1));
	cd->new_pwd = getcwd(NULL, 0);
	if (update_old_pwd(cd, shell))
		return (1);
	if (update_new_pwd(cd, shell))
		return (1);
	return (0);
}

int	exec_cd_ctrl(t_pipe *pipex, char **cmd_args, t_shell *shell)
{
	t_cd	cd;

	cd.old_pwd = NULL;
	cd.new_pwd = NULL;
	cd.cmd_count = pipex->cmd_count;
	if (exec_cd(cmd_args, shell, &cd))
		return (1);
	free(cd.old_pwd);
	free(cd.new_pwd);
	return (0);
}

/* Universal start but malloc allocation / freeing heavy / incomplete freeing
static int	update_env_line(char *env_label, char *nl, t_shell *sh, t_cd cd)
{
	int	i;
	char	**new_envp;
    char    *search;

	i = 0;
	if (getenv(env_label))
	{
		search = ft_strjoin(env_label, "=");
        if (!search)
            perror_exit("cd: memory allocation fail");
        while (strncmp(shell->envp[i], "OLDPWD=", 7) != 0)
        		i++;
		free(shell->envp[i]);
        shell->envp[i] = ft_strjoin("OLDPWD=", nl);
		if (!shell->envp[i])
			perror_exit("cd: memory allocation fail");
	}
	if (shell->envp[i] != NULL)
	{   
		while (shell->envp[i] != NULL)
			i++;
        new_envp = append_shell_envp(shell, i, nl);
		if (!new_envp)
			perror_exit("cd new_envp allocation fail");
	}
	return (0);
}*/