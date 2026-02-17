/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:05:31 by psmolich          #+#    #+#             */
/*   Updated: 2026/02/16 11:38:26 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Parses a single-quoted string and returns the contained word.
static char	*parse_single_quote(char *line, int *index)
{
	int		start;
	char	*word;

	(*index)++;
	start = *index;
	while (line[*index] && line[*index] != SQ)
		(*index)++;
	if (line[*index] == '\0')
		return (NULL);
	word = ft_substr(line, start, *index - start);
	(*index)++;
	return (word);
}

// Checks if the character is valid for variable names
// (alphanumeric or underscore).
static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

// The function extracts the variable name following the "$" sign,
// searches for it in the environment variables,
// and returns the corresponding value.
// If the variable is not found, it returns an empty string.
static char	*expand_env(char *line, int *index, t_shell shell)
{
	char	*var_name;
	int		i;
	int		var_len;

	(*index)++;
	if (line[*index] == '?')
		return ((*index)++, ft_itoa(shell.last_status));
	var_len = 0;
	while (is_valid_var_char(line[(*index) + var_len]))
		var_len++;
	if (var_len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(line, (*index), var_len);
	if (!var_name)
		return (NULL);
	(*index) += var_len;
	i = 0;
	while (shell.envp && shell.envp[i])
	{
		if (ft_strncmp(shell.envp[i], var_name, var_len) == 0
			&& shell.envp[i][var_len] == '=')
			return (free(var_name), ft_strdup(shell.envp[i] + var_len + 1));
		i++;
	}
	return (free(var_name), ft_strdup(""));
}

// Parses double-quoted string, handling variable expansion if needed,
// and returns the contained word.
static char	*parse_double_quote(char *line, int *index,
	t_shell shell, int expand)
{
	char	*word;
	char	*temp;

	(*index)++;
	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (line[*index] && line[*index] != DQ)
	{
		if (line[*index] == '$' && expand)
			temp = expand_env(line, index, shell);
		else
			temp = char_to_str(line[(*index)++]);
		if (!temp)
			return (free(word), NULL);
		word = ft_strjoin_free(word, temp);
		if (!word)
			return (NULL);
	}
	if (line[*index] == '\0')
		return (free(word), NULL);
	(*index)++;
	return (word);
}

char	*parse_word(char *line, t_shell shell, int expand)
{
	char	*word;
	int		i;
	char	*temp;

	word = ft_strdup("");
	if (!word)
		return (error_msg(ERR_MEMORY), NULL);
	i = 0;
	while (line[i] && !ft_isspace(line[i]) && !is_special(line[i]))
	{
		if (line[i] == SQ)
			temp = parse_single_quote(line, &i);
		else if (line[i] == DQ)
			temp = parse_double_quote(line, &i, shell, expand);
		else if (line[i] == '$' && expand)
			temp = expand_env(line, &i, shell);
		else
			temp = char_to_str(line[i++]);
		if (!temp)
			return (error_msg(ERR_MEMORY), free(word), NULL);
		word = ft_strjoin_free(word, temp);
		if (!word)
			return (error_msg(ERR_MEMORY), NULL);
	}
	return (word);
}
