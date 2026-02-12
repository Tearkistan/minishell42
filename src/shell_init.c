/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:42:22 by twatson           #+#    #+#             */
/*   Updated: 2026/01/14 12:46:10 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
	return (copy) ;
}

void	shell_init(t_shell *shell, char **envp)
{
	shell->envp = copy_envp(shell->envp, envp, 1);
	shell->last_status = 0;
	shell->running = 1;
	shell->envp_len = 0;
	while (shell->envp[shell->envp_len])
		shell->envp_len++;
	set_signals_prompt_mode();
	return ; 
}
