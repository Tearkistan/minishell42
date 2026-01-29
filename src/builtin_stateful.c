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

static int  update_old_pwd(char *old_pwd, char **envp)
{
    /* Search "OLDPWD="
    if exist replace
    else append 
    using strncmp, strjoin, free */
    (void)old_pwd;
    (void)envp;
    return (0);
}

static int  update_new_pwd(char *new_pwd, char **envp)
{
    /* Search "OLDPWD="
    if exist replace
    else append 
    using strncmp, strjoin, free */
    (void)new_pwd;
    (void)envp;
    return (0);
}

int	exec_cd(t_pipe *pipex, char **cmd_args, char **envp)
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
    if (update_old_pwd(old_pwd, envp))
        return (1);
    if (update_new_pwd(new_pwd, envp))
        return (1);
    return (0);
}

int	exec_exit(char **cmd_args, char **envp)
{
    (void)cmd_args;
    (void)envp;
    return (0);
}

int	exec_unset(char **cmd_args, char **envp){
    (void)cmd_args;
    (void)envp;
    return (0);
}

int	exec_export(char **cmd_args, char **envp){
    (void)cmd_args;
    (void)envp;
    return (0);
}