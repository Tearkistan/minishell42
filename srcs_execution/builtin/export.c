/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:37:48 by twatson           #+#    #+#             */
/*   Updated: 2026/04/10 14:32:59 by psmolich         ###   ########.fr       */
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
	int	sort_len;

	i = 0;
	sort_len = shell->envp_len + shell->no_eq_len;
	while (i < sort_len)
	{
		j = 0;
		while (j < (sort_len - i - 1))
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
	while (arg[i] != '+' && arg[i] != '=' && arg[i] != '\0')
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
	while (arg[i] != '\0')
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
		reset_exec_loop(cmd_args[i], shell, export);
		if (parse_export_arg(cmd_args[i], export) == -1)
		{
			export->valid = 0;
			i++;
			continue ;
		}
		if (!export->eq)
			add_no_equal_key(export, shell);
		else
		{
			export->new_line = create_line(export->key, export->value);
			if (!export->new_line)
				exit_export(export, shell, 1);
		}
		index = find_var_in_env(shell, export);
		finish_export_arg(shell, export, index);
		i++;
	}
}

void	exit_export(t_export *export, t_shell *shell, int alloc_fail)
{
	if (alloc_fail)
		perror("export");
	shell->last_status = !export->valid;
	if (export->temp_envp)
		free_matrix(export->temp_envp);
	if (export->key)
		free(export->key);
	if (export->value)
		free(export->value);
	if (!alloc_fail && shell->last_status == 1)
		error_msg(ERR_NOT_VALID_ID, "export");
	if (export->parent && alloc_fail)
	{
		shell->running = 0;
		shell->last_status = 1;
	}
	else if (alloc_fail)
		exit(1);
}

/* generous no_eq allocation */
int	exec_export_ctrl(char **cmd_args, t_shell *shell, int parent)
{
	t_export	export;

	export.temp_envp = join_envp_no_eq(shell);
	if (!export.temp_envp)
		exit_export(&export, shell, 1);
	export.new_line = NULL;
	export.key = NULL;
	export.value = NULL;
	export.arg_count = 0;
	export.parent = parent;
	export.append = 0;
	export.eq = 1;
	export.valid = 1;
	while (cmd_args[export.arg_count])
		export.arg_count++;
	if (export.arg_count == 1)
		sort_to_print(shell, &export);
	else
		exec_export(cmd_args, shell, &export);
	exit_export(&export, shell, 0);
	return (0);
}
