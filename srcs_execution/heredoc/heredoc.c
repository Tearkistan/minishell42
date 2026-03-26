/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:18:48 by twatson           #+#    #+#             */
/*   Updated: 2026/03/25 14:45:00 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_line(char **line, t_shell shell, int quote_delim)
{
	int		i;
	char	*word;
	char	*temp;

	if (quote_delim == TRUE)
		return (*line);
	word = ft_strdup("");
	if (!word)
		return (NULL);
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
			temp = expand_env(*line, &i, shell);
		else
			temp = char_to_str((*line)[i++]);
		if (!temp)
			return (free(word), NULL);
		word = ft_strjoin_free(word, temp);
		if (!word)
			return (NULL);
	}
	free(*line);
	return (word);
}

static int	heredoc_break_conditions(char *line, char *target)
{
	if (!line)
		return (error_msg(HD_EOF, target), TRUE);
	else if (ft_strcmp(line, target) == 0)
		return (free(line), TRUE);
	return (FALSE);
}

int	heredoc_read(t_redirects *redir, t_pipe *pipex, t_shell *shell)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(HD_PROMPT);
		if (g_sig == SIGINT)
			return (resolve_heredoc_sigint(line, shell, pipex), -1);
		if (heredoc_break_conditions(line, redir->target))
			break ;
		line = expand_line(&line, *shell, redir->quote_delim);
		if (!line)
			return (error_msg(ERR_MEMORY, NULL), -1);
		if (write(pipex->hd_pipe[1], line, ft_strlen(line)) == -1
			|| write(pipex->hd_pipe[1], "\n", 1) == -1)
			return (error_msg(ERR_WRITE, "here-document"), -1);
		free(line);
	}
	return (0);
}
