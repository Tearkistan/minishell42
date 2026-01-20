/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:58:31 by twatson           #+#    #+#             */
/*   Updated: 2026/01/20 13:58:50 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **cmd_args, char *arg, char **envp)
{
	char	**dirs;
	char	*path_value;
	char	*path;

	if (access(arg, F_OK) == 0)
	{
		if (access(arg, X_OK) == 0)
			return (ft_strdup(arg));
		else
			permission_denied_exit(cmd_args);
	}
	path_value = get_env_path(envp);
	dirs = ft_split(path_value, ':');
	if (!dirs)
		return (NULL);
	path = find_cmd(dirs, cmd_args, arg);
	free_matrix(dirs);
	return (path);
}

char	*find_cmd(char **dirs, char **cmd_args, char *arg)
{
	char	*full_path;
	int		i;
	int		found_and_denied;

	i = 0;
	found_and_denied = 0;
	while (dirs && dirs[i])
	{
		full_path = join_paths(dirs[i], arg);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
				return (full_path);
			else
				found_and_denied = 1;
		}
		free(full_path);
		i++;
	}
	if (found_and_denied == 1)
	{
		free_matrix(dirs);
		permission_denied_exit(cmd_args);
	}
	return (NULL);
}

char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*join_paths(char *dir, char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		msg_exit("join_paths - temp: memory allocation failed");
	full = ft_strjoin(temp, cmd);
	if (!full)
		msg_exit("join_paths - full: memory allocation failed");
	free(temp);
	return (full);
}
