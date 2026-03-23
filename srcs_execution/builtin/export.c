/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:37:48 by twatson           #+#    #+#             */
/*   Updated: 2026/03/23 08:01:38 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cases:
	1. No args - print declare - x KEY="VALUE"
	2. arg = NAME=VALUE - set or replace env, if VALUE "", that becomes value
	3. arg = NAME - check if it exists in envp and add (without =) if not
	"+=" adds (joins) characters
	should be sorted - bubble!
	*/

static void	sort_to_print(t_shell *shell, t_export *export)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->envp_len)
	{
		j = 0;
		while (j < (shell->envp_len - i - 1))
		{
			if (ft_strcmp(export->temp_envp[j], export->temp_envp[j + 1]) > 0)
			{
				export->new_line = export->temp_envp[j + 1];
				export->temp_envp[j + 1] = export->temp_envp[j];
				export->temp_envp[j] = export->new_line;
			}
			j++;
		}
		i++;
	}
	export->new_line = NULL;
	print_export(export->temp_envp, shell->no_eq);
}

static int	parse_export_arg(char *arg, t_export *export)
{
	int	i;
	int	j;

	if (export_arg_error(arg, export))
		return (-1);
	i = 0;
	while (arg[i] != '+' || arg[i] != '=' || arg[i] != '\0')
	{
		export->key[i] = arg[i];
		i++;
	}
	export->key[i] = '\0';
	if (arg[i] == '\0')
	{
		export->eq = 0;
		return (0);
	}
	if (arg[i] == '+')
		i++;
	i++;
	j = 0;
	while (arg[i] == '\0')
		export->value[j++] = arg[i++];
	export->value[j] = '\0';
	return (0);
}

static void	exec_export(char **cmd_args, t_shell *shell, t_export *export)
{
	int		i;
	int		index;

	i = 1;
	while (cmd_args[i])
	{
		alloc_key_value(cmd_args[i], export, shell);
		if (parse_export_arg(cmd_args[i], export) == -1)
		{
			shell->last_status = 1;
			i++;
			continue ;
		}
		if (export->eq == 0)
			add_no_equal_key(export, shell);
		export->new_line = create_line(export->key, export->value);
		if (!export->new_line)
			exit_export(export, shell, 1);
		index = find_var_in_env(shell->envp, export->key);
		finish_export_arg(shell, export, index);
		i++;
	}
}

void	exit_export(t_export *export, t_shell *shell, int alloc_fail)
{
	if (export->temp_envp)
		free_matrix(export->temp_envp);
	if (export->new_line)
		free(export->new_line);
	if (export->key)
		free(export->key);
	if (export->value)
		free(export->value);
	if (shell->last_status == 1)
		error_msg("export: not a valid identifier");
	if (export->parent && alloc_fail)
	{
		shell->running = 0;
		shell->last_status = 1;
	}
	else if (alloc_fail)
	{
		error_msg("export: memory allocation error");
		exit(1);
	}
}

/* generous no_eq allocation */
int	exec_export_ctrl(char **cmd_args, t_shell *shell, int parent)
{
	t_export	export;

	export.temp_envp = NULL;
	export.temp_envp = copy_envp(export.temp_envp, shell->envp, 1);
	export.new_line = NULL;
	export.key = NULL;
	export.value = NULL;
	export.arg_count = 0;
	export.parent = parent;
	export.append = 0;
	export.eq = 1;
	while (cmd_args[export.arg_count])
		export.arg_count++;
	if (export.arg_count == 1)
		sort_to_print(shell, &export);
	else
		exec_export(cmd_args, shell, &export);
	exit_export(&export, shell, 0);
	return (0);
}
