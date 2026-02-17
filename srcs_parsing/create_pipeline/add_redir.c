/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:23:50 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:37:56 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_redir_back(t_pipeline *current, t_redirects *new_redir)
{
	t_redirects	*current_redir;

	if (!new_redir)
		return (FAILURE);
	if (!current->cmd.redirects)
		current->cmd.redirects = new_redir;
	else
	{
		current_redir = current->cmd.redirects;
		while (current_redir->next)
			current_redir = current_redir->next;
		current_redir->next = new_redir;
	}
	return (SUCCESS);
}

int	add_redir(t_pipeline *current, t_token **token, t_shell shell)
{
	t_redirects	*redir;

	redir = malloc(sizeof(t_redirects));
	if (!redir)
		return (error_msg(ERR_MEMORY), FAILURE);
	if (ft_strcmp((*token)->value, ">") == 0)
		redir->type = REDIR_OUT;
	else if (ft_strcmp((*token)->value, "<") == 0)
		redir->type = REDIR_IN;
	else if (ft_strcmp((*token)->value, ">>") == 0)
		redir->type = REDIR_APP;
	else
		redir->type = HEREDOC;
	(*token) = (*token)->next;
	redir->target = parse_word((*token)->value, shell,
			redir->type != HEREDOC);
	if (!redir->target)
		return (free(redir), FAILURE);
	redir->quote_delim = has_quotes((*token)->value);
	redir->next = NULL;
	return (add_redir_back(current, redir));
}
