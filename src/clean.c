/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:43:32 by twatson           #+#    #+#             */
/*   Updated: 2026/01/23 13:25:34 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	int			i;
	t_redirects	*curr;
	t_redirects	*tmp;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		cmd->args = NULL;
	}
	curr = &cmd->redirects;
	while (curr)
	{
		tmp = curr->next;
		if (curr->target)
			free(curr->target);
		free(curr);
		curr = tmp;
	}
}


static void	free_pipeline(t_pipeline *pipeline)
{
	t_pipeline	*temp;
	t_pipeline	*curr;

	if (!pipeline)
		return ;
	curr = pipeline;
	while (curr)
	{
		temp = curr->next;
		free_cmd(&curr->cmd);
		if (curr != pipeline)
			free(curr);
		curr = temp;
	}
}

static void	free_shell(t_shell *shell)
{
	int	i;

	if (!shell || !shell->envp)
		return ;
	i = 0;
	while (shell->envp[i])
		free(shell->envp[i++]);
	free(shell->envp);
}

void	clean_up(t_shell *shell, t_pipeline *pipeline,
	char *line, char *err_msg)
{
	if (shell)
		free_shell(shell);
	if (pipeline)
		free_pipeline(pipeline);
	if (err_msg && !ft_strncmp(err_msg, "exit", 5))
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (line)
		free(line);
	else if (err_msg)
		perror_exit(err_msg);
}
