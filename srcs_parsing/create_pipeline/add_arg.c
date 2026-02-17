/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:24:51 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:37:50 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_arg(t_pipeline *current, t_token token, t_shell shell)
{
	int		i;
	char	**new_args;

	i = 0;
	while (current->cmd.args && current->cmd.args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (error_msg(ERR_MEMORY), FAILURE);
	i = 0;
	while (current->cmd.args && current->cmd.args[i])
	{
		new_args[i] = ft_strdup(current->cmd.args[i]);
		if (!new_args[i])
			return (error_msg(ERR_MEMORY), free_args(new_args), FAILURE);
		i++;
	}
	new_args[i] = parse_word(token.value, shell, TRUE);
	if (!new_args[i])
		return (free_args(new_args), FAILURE);
	new_args[i + 1] = NULL;
	free_args(current->cmd.args);
	current->cmd.args = new_args;
	return (SUCCESS);
}
