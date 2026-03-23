/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:42:22 by twatson           #+#    #+#             */
/*   Updated: 2026/03/23 13:25:58 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_matrix(char **copy, char **original)
{
	int	size;

	size = 0;
	while (original[size] != NULL)
		size++;
	copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copy)
		perror_exit("envp copy array allocation failed");
	return (copy);
}

char	**copy_envp(char **copy, char **original, int allocate)
{
	int	i;

	if (allocate)
		copy = allocate_matrix(copy, original);
	i = 0;
	while (original[i] != NULL)
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
		{
			free(copy);
			perror_exit("envp variable failed to copy");
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	numeric_shlvl_exists(char **envp, int *index)
{
	int		n_len;
	char	*n_str;
	int		n;

	while (envp[(*index)])
	{
		if (ft_strncmp(envp[(*index)], "SHLVL=", 6) == 0)
		{
			n_len = ft_strlen(envp[(*index)]) - 6;
			n_str = ft_substr(envp[(*index)], 6, n_len);
			if (!n_str)
				perror_exit("shlvl allocation fail");
			n = ft_atoi(n_str);
			free(n_str);
			if (n)
				return (n);
		}
		(*index)++;
	}
	return (0);
}

static void	add_shlvl(t_shell *shell)
{
	int		shlvl;
	int		index;
	char	*n_to_str;
	char	*new_shlvl;

	index = 0;
	shlvl = 0;
	shlvl = numeric_shlvl_exists(shell->envp, &index);
	if (shlvl++)
	{
		n_to_str = ft_itoa(shlvl);
		if (!n_to_str)
			perror_exit("shlvl allocation fail");
		new_shlvl = ft_strjoin("SHLVL=", n_to_str);
		if (!new_shlvl)
			perror_exit("shlvl allocation fail");
		free(n_to_str);
		free(shell->envp[index]);
		shell->envp[index] = new_shlvl;
	}
	else
	{
		if (!(append_shell_envp(shell, "SHLVL=1")))
			perror_exit("shlvl append fail");
	}
}

void	shell_init(t_shell *shell, char **envp)
{
	shell->envp = copy_envp(shell->envp, envp, 1);
	add_shlvl(shell);
	shell->last_status = 0;
	shell->running = 1;
	shell->envp_len = 0;
	while (shell->envp[shell->envp_len])
		shell->envp_len++;
	shell->no_eq = (char **)malloc(sizeof(char *) * (shell->envp_len + 420));
	shell->no_eq[0] = NULL;
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	set_signals_prompt_mode();
	return ;
}
