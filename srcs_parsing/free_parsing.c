/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FREE.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:51:17 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:38:13 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

void	free_args(char **args)
{
	if (args)
		ft_free_arr(args);
}

void	free_redirects(t_redirects *redir)
{
	t_redirects	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		if (temp->target)
			free(temp->target);
		free(temp);
	}
}

void	free_pipeline(t_pipeline *pipeline)
{
	t_pipeline	*current;
	t_pipeline	*temp;

	current = pipeline;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->cmd.args)
			free_args(temp->cmd.args);
		if (temp->cmd.redirects)
			free_redirects(temp->cmd.redirects);
		free(temp);
	}
}
