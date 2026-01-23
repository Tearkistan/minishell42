// #include "minishell.h"

// int	parse_line(t_pipeline *pipeline, char *line, t_shell *shell)
// {
// 	(void) pipeline;
// 	(void) line;
// 	(void) shell; /* read-only purpose to expand environment variables */
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:31:32 by psmolich          #+#    #+#             */
/*   Updated: 2026/01/23 09:50:40 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char *s, int *i)
{
	while (s[*i] && is_space(s[*i]))
		(*i)++;
}

// static char	*str_join_free(char *s1, char *s2)
// {
// 	char *res;
// 	int len1 = s1 ? strlen(s1) : 0;
// 	int len2 = s2 ? strlen(s2) : 0;

// 	res = malloc(len1 + len2 + 1);
// 	if (!res)
// 		return NULL;
// 	if (s1) memcpy(res, s1, len1);
// 	if (s2) memcpy(res + len1, s2, len2);
// 	res[len1 + len2] = '\0';
// 	free(s1);
// 	free(s2);
// 	return res;
// }

/* ===== ENV ===== */

// static char *get_env(char *name, t_shell *shell)
// {
// 	int i = 0;
// 	int len = strlen(name);

// 	while (shell->envp && shell->envp[i])
// 	{
// 		if (!strncmp(shell->envp[i], name, len)
// 			&& shell->envp[i][len] == '=')
// 			return strdup(shell->envp[i] + len + 1);
// 		i++;
// 	}
// 	return strdup("");
// }

// static char *expand_env(char *line, int *i, t_shell *shell)
// {
// 	char buf[256];
// 	int j = 0;

// 	(*i)++;
// 	while (line[*i] && (isalnum(line[*i]) || line[*i] == '_'))
// 		buf[j++] = line[(*i)++];
// 	buf[j] = '\0';

// 	return get_env(buf, shell);
// }

static char	*ft_strndup(const char *s, size_t size)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*expand_env(char *line, int *i, t_shell *shell)
{
	char	*buffer;
	int		j;
	int		len;

	(*i)++;
	len = 0;
	while (line[(*i) + len]
		&& (ft_isalnum(line[(*i) + len]) || line[(*i) + len] == '_'))
		len++;
	buffer = ft_strndup(line + (*i), len);
	if (!buffer)
		return (NULL); //error memory alloc
	j = 0;
	while (shell->envp && shell->envp[j])
	{
		if (!ft_strncmp(shell->envp[j], buffer, len)
			&& shell->envp[j][len] == '=')
			return (free(buffer), ft_strdup(shell->envp[j] + len + 1));
		j++;
	}
	return (free(buffer), ft_strdup(""));
}

/* ===== WORD PARSER ===== */

static char *parse_word(char *line, int *i, t_shell *shell)
{
	char *res = strdup("");
	int mode = NORMAL;

	while (line[*i])
	{
		if (mode == NORMAL)
		{
			if (is_space(line[*i]) || line[*i] == '|' || is_redir(line[*i]))
				break;
			else if (line[*i] == '\'')
				mode = SQ, (*i)++;
			else if (line[*i] == '"')
				mode = DQ, (*i)++;
			else if (line[*i] == '$')
				res = str_join_free(res, expand_env(line, i, shell));
			else
				res = str_join_free(res, strndup(&line[(*i)++], 1));
		}
		else if (mode == SQ)
		{
			if (line[*i] == '\'')
				mode = NORMAL, (*i)++;
			else
				res = str_join_free(res, strndup(&line[(*i)++], 1));
		}
		else if (mode == DQ)
		{
			if (line[*i] == '"')
				mode = NORMAL, (*i)++;
			else if (line[*i] == '$')
				res = str_join_free(res, expand_env(line, i, shell));
			else
				res = str_join_free(res, strndup(&line[(*i)++], 1));
		}
	}
	if (mode != NORMAL)
		return NULL;
	return res;
}

/* ===== REDIRECTION ===== */

static t_redirects *redir_new(int type, char *target, int q)
{
	t_redirects *r = malloc(sizeof(t_redirects));
	if (!r)
		return NULL;
	r->type = type;
	r->target = target;
	r->quote_delim = q;
	r->next = NULL;
	return r;
}

static t_redirects *parse_redirect(char *line, int *i, t_shell *shell)
{
	int type;
	int q = NORMAL;
	char *target;

	if (line[*i] == '<' && line[*i + 1] == '<')
		type = HEREDOC, *i += 2;
	else if (line[*i] == '<')
		type = IN, (*i)++;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		type = APPEND, *i += 2;
	else
		type = OUT, (*i)++;

	skip_spaces(line, i);
	if (!line[*i] || line[*i] == '|')
		return NULL;

	if (type == HEREDOC)
	{
		if (line[*i] == '\'') q = SQ;
		else if (line[*i] == '"') q = DQ;
		target = parse_word(line, i, shell);
	}
	else
		target = parse_word(line, i, shell);

	if (!target)
		return NULL;
	return redir_new(type, target, q);
}

/* ===== COMMAND ===== */

static int parse_cmd(t_cmd *cmd, char *line, int *i, t_shell *shell)
{
	char **args = NULL;
	int argc = 0;
	t_redirects *r_head = NULL, *r_last = NULL;

	while (line[*i] && line[*i] != '|')
	{
		skip_spaces(line, i);
		if (is_redir(line[*i]))
		{
			t_redirects *r = parse_redirect(line, i, shell);
			if (!r)
				return 1;
			if (!r_head)
				r_head = r;
			else
				r_last->next = r;
			r_last = r;
		}
		else if (line[*i])
		{
			char *w = parse_word(line, i, shell);
			if (!w)
				return 1;
			args = realloc(args, sizeof(char *) * (argc + 2));
			args[argc++] = w;
			args[argc] = NULL;
		}
	}
	cmd->args = args;
	cmd->redirects = r_head;
	return 0;
}

/* ===== PIPELINE ===== */

int parse_line(t_pipeline *pipeline, char *line, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (line[i] == '|')
			return 1;
		if (parse_cmd(&cur->cmd, line, &i, shell))
			return 1;
		skip_spaces(line, &i);
		if (line[i] == '|')
		{
			cur->next = calloc(1, sizeof(t_pipeline));
			cur = cur->next;
			i++;
		}
	}
	return 0;
}



