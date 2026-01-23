/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:42:22 by twatson           #+#    #+#             */
/*   Updated: 2026/01/23 10:43:20 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// static void	allocate_matrix(t_shell *shell, char **envp)
// {
// 	int	size;

// 	size = 0;
// 	while (envp[size] != NULL)
// 		size++;
// 	shell->envp = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (!shell->envp)
// 		perror_exit("envp copy array allocation failed");
// 	return ;
// }


// static void	copy_envp(t_shell *shell, char **envp)
// {
// 	int	i;

// 	allocate_matrix(shell, envp);
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		shell->envp[i] = ft_strdup(envp[i]);
// 		if (!shell->envp[i])
// 		{
// 			free(shell->envp);
// 			perror_exit("envp variable failed to copy");
// 		}
// 		i++;
// 	}
// 	return ;
// }

static void	copy_envp(t_shell *shell, char **envp)
{
	int	i;
	int	size;

	size = 0;
	while (envp[size])
		size++;
	shell->envp = malloc(sizeof(char *) * (size + 1));
	if (!shell->envp)
		perror_exit("envp copy array allocation failed");
	i = 0;
	while (i < size)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i])
		{
			while (i > 0)
				free(shell->envp[--i]);
			free(shell->envp);
			perror_exit("envp variable failed to copy");
		}
		i++;
	}
	shell->envp[i] = NULL;
}

void	shell_init(t_shell *shell, char **envp)
{
	copy_envp(shell, envp);
	shell->last_status = 0;
	set_signals_prompt_mode();
}
