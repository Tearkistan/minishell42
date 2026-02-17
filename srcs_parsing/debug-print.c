/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRINT.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:11:24 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:38:33 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	ft_printf(P "+++++++++++++++++++++++++++++++++++++++++++++++++\n+" R);
	ft_printf("\t\tEnvironment Variables:\t\t");
	ft_printf(P "+\n+++++++++++++++++++++++++++++++++++++++++++++++++\n\n" R);
	while (envp[i])
		ft_printf("\t%s\n", envp[i++]);
	ft_printf(P "\n+++++++++++++++++++++++++++++++++++++++++++++++++\n" R);
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	ft_printf(G "+++++++++++++++++++++++++++++++++++++++++++++++++\n" R);
	ft_printf("\t\tTokens:\t\t\n");
	ft_printf(G "+++++++++++++++++++++++++++++++++++++++++++++++++\n\n" R);
	if (!current)
		ft_printf("\tno tokens\n");
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			ft_printf(G "\tType: PIPE\n" R);
		else if (current->type == TOKEN_REDIR)
			ft_printf(Y "\tType: REDIR, Value: %s\n" R, current->value);
		else if (current->type == TOKEN_WORD)
			ft_printf("\tType: WORD, Value: %s\n", current->value);
		current = current->next;
	}
	ft_printf(G "\n+++++++++++++++++++++++++++++++++++++++++++++++++\n" R);
}

void	print_pipeline(t_pipeline *pipeline)
{
	t_pipeline	*current;
	int			i;
	int			pipe_num;
	t_redirects	*redir;

	ft_printf(Y "+++++++++++++++++++++++++++++++++++++++++++++++++\n" R);
	ft_printf("\t\tPipeline:\t\t");
	ft_printf(Y "\n+++++++++++++++++++++++++++++++++++++++++++++++++\n\n" R);
	current = pipeline;
	if (!current)
	{
		ft_printf("\tPipeline is NULL\n");
		return ;
	}
	pipe_num = 0;
	while (current)
	{
		ft_printf("Pipeline%d:\n", pipe_num++);
		i = 0;
		ft_printf("├─ Args: ");
		if (!current->cmd.args)
			ft_printf("NULL\n");
		else
		{
			while (current->cmd.args[i])
				ft_printf("%s ", current->cmd.args[i++]);
			ft_printf("\n");
		}
		redir = current->cmd.redirects;
		if (!redir)
			ft_printf("└─ Redirects: NULL\n");
		else
		{
			while (redir)
			{
				if (redir->type == REDIR_IN)
					ft_printf("└─ Redirect: IN, Target %s, ", redir->target);
				else if (redir->type == REDIR_OUT)
					ft_printf("└─ Redirect: OUT, Target %s, ", redir->target);
				else if (redir->type == HEREDOC)
					ft_printf("└─ Redirect: HEREDOC, Target %s, ", redir->target);
				else if (redir->type == REDIR_APP)
					ft_printf("└─ Redirect: APP, Target %s, ", redir->target);
				if (redir->quote_delim)
					ft_printf("Quote Delimiter: YES\n");
				else
					ft_printf("Quote Delimiter: NO\n");
				redir = redir->next;
			}
		}
		current = current->next;
	}
	ft_printf(Y "\n+++++++++++++++++++++++++++++++++++++++++++++++++\n" R);
}
