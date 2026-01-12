/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:20:15 by mnussler          #+#    #+#             */
/*   Updated: 2025/09/20 16:20:16 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Parses command string into argument array with command and args
 * @param cmd Command structure to populate
 * @param cmd_str Command string to split by spaces
 *
 * @note `"cat file.txt"` becomes
 *
 * - `cmd->argv[0] = "cat"` (command name)
 *
 * - `cmd->argv[1] = "file.txt"` (argument)
 *
 * - `cmd->argv[2] = NULL` (terminator)
 *
 * - `cmd->path` will be resolved to full path like `/bin/cat` later
 */
void	parse_command(t_cmd *cmd, char *cmd_str)
{
	cmd->argv = ft_split(cmd_str, ' ');
	cmd->path = NULL;
}

/**
 * @brief Finds environment variable value by name
 * @param envp Environment variables array
 * @param var Variable name to search for
 * @return Pointer to variable value or NULL if not found
 */
static char	*find_env_var(char **envp, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * @brief Searches for executable in PATH directories
 * @param path_dirs Array of directories to search
 * @param cmd_name Command name to find
 * @return Full path to executable or NULL if not found
 *
 * @note Search process
 *
 * - Create program path from path dir: `dir + "/" + cmd`
 *
 * - test if file exists and is executable: `access(candidate, F_OK | X_OK)`
 *
 * - Returns first valid path found, or NULL if none found
 *
 * - Frees temporary strings during search
 */
static char	*search_in_path_dirs(char **path_dirs, char *cmd_name)
{
	char	*temp;
	char	*candidate;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		temp = ft_strjoin(path_dirs[i], "/");
		candidate = ft_strjoin(temp, cmd_name);
		free(temp);
		if (access(candidate, F_OK | X_OK) == 0)
			return (candidate);
		free(candidate);
		i++;
	}
	return (NULL);
}

/**
 * @brief Frees PATH directories array from ft_split
 * @param path_dirs Array of PATH directories to free
 */
static void	free_path_dirs(char **path_dirs)
{
	int	i;

	i = 0;
	while (path_dirs[i])
	{
		free(path_dirs[i]);
		i++;
	}
	free(path_dirs);
}

/**
 * @brief Resolves command name to full executable path
 * @param cmd Command structure to update with path
 * @param envp Environment variables containing PATH
 *
 * @note Resolution process
 *
 * - test if cmd contains '/' to determine if cmd path is abs/rel
 *
 * - get PATH value from environment: `find_env_var()`
 *
 * - find command in path_dir + "/" + cmd: `search_in_path_dirs()`
 *
 * - Store original command name if not found (let execve handle the error)
 */
void	resolve_command_path(t_cmd *cmd, char **envp)
{
	char	*path_env;
	char	**path_dirs;

	if (ft_strchr(cmd->argv[0], '/'))
	{
		cmd->path = ft_strdup(cmd->argv[0]);
		return ;
	}
	path_env = find_env_var(envp, "PATH");
	if (!path_env)
	{
		cmd->path = ft_strdup(cmd->argv[0]);
		return ;
	}
	path_dirs = ft_split(path_env, ':');
	cmd->path = search_in_path_dirs(path_dirs, cmd->argv[0]);
	free_path_dirs(path_dirs);
	if (!cmd->path)
		cmd->path = ft_strdup(cmd->argv[0]);
}
