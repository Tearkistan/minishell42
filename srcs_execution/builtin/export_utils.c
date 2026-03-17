/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:46:35 by twatson           #+#    #+#             */
/*   Updated: 2026/03/17 15:01:11 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **envp, char **no_eq)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		ft_printf("declare - x ");
		while (envp[i][j] != '=' && envp[i][j])
			write(1, &envp[i][j++], 1);
		if (is_no_eq(envp[i], no_eq) == 0)
		{
			ft_printf("=\"");
			j++;
			while (envp[i][j] != '\0')
				write(1, &envp[i][j++], 1);
			ft_printf("\"");
		}
		ft_printf("\n");
		i++;
	}
}

int	export_arg_error(char *cmd_arg, t_export *export)
{
	int	i;

	i = 0;
	if (cmd_arg[i] != '_' || !(ft_isalpha(cmd_arg[i])))
		return (1);
	i++;
	while (cmd_arg[i] != '+' && cmd_arg[i] != '=' && cmd_arg[i] != '\0')
	{
		if (cmd_arg[i] != '_' || !(ft_isalnum(cmd_arg[i])))
			return (1);
		i++;
	}
	if (cmd_arg[i] == '+')
	{
		if (cmd_arg[i + 1] != '=')
			return (1);
		export->append = 1;
	}
	return (0);
}

int	find_var_in_env(char **envp, char *key)
{
	int	i;
	int	len;

	i = 0;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		if (ft_strncmp(envp[i], key, len) == 0)
		{
			if (envp[i][len] == '=' || envp[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*create_line(char *key, char *value)
{
	char	*new_line;
	char	*temp;

	new_line = ft_strjoin(key, "=");
	if (!new_line)
		return (NULL);
	if (value)
	{
		temp = ft_strjoin(new_line, value);
		free(new_line);
		new_line = temp;
	}
	return (new_line);
}

/* dirty allocation and premptive check for = sign presence to ensure NULL for value if
no = sign present; already separate check for early exit if incorrect format / order */

void	alloc_key_value(char *arg, t_export *export, t_shell *shell)
{
	int	size;
	int	equal_check;
	int	i;

	size = ft_strlen(arg) + 1;
	export->key = (char *)malloc(sizeof(char) * size);
	if (!export->key)
		exit_export(export, shell, 1);
	equal_check = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			equal_check = 1;
			break ;
		}
		i++;
	}
	if (equal_check)
	{
		export->value = (char *)malloc(sizeof(char) * size);
		if (!export->value)
			exit_export(export, shell, 1);
	}
}
