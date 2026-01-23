/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:34:56 by psmolich          #+#    #+#             */
/*   Updated: 2026/01/23 13:54:22 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

// static char *extract_word(char *line, int *i, int *state, int *join)
// {
// 	int start = *i;
// 	int local_state = NORMAL;
// 	int local_join = FALSE;

// 	while (line[*i] && !isspace(line[*i]) && line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
// 	{
// 		if (line[*i] == '\'')
// 		{
// 			if (local_state == NORMAL)
// 				local_state = SQ;
// 			else if (local_state != SQ)
// 				local_join = TRUE;
// 			(*i)++;
// 			while (line[*i] && line[*i] != '\'')
// 				(*i)++;
// 			if (line[*i])
// 				(*i)++;
// 		}
// 		else if (line[*i] == '"')
// 		{
// 			if (local_state == NORMAL)
// 				local_state = DQ;
// 			else if (local_state != DQ)
// 				local_join = TRUE;
// 			(*i)++;
// 			while (line[*i] && line[*i] != '"')
// 				(*i)++;
// 			if (line[*i])
// 				(*i)++;
// 		}
// 		else
// 			(*i)++;
// 	}
// 	*state = local_state;
// 	*join = local_join;

// 	// Usuń zewnętrzne cudzysłowy
// 	int len = *i - start;
// 	char *raw = strndup(line + start, len);
// 	char *res;

// 	if (local_state == SQ || local_state == DQ)
// 	{
// 		if (len >= 2)
// 			res = strndup(raw + 1, len - 2);
// 		else
// 			res = strdup("");
// 		free(raw);
// 	}
// 	else
// 		res = raw;

// 	return res;
// }

// static t_token *new_token(int type, char *value, int state, int join)
// {
// 	t_token *tok = malloc(sizeof(t_token));
// 	if (!tok)
// 		return NULL;
// 	tok->type = type;
// 	tok->value = value;
// 	tok->state = state;
// 	tok->join = join;
// 	tok->next = NULL;
// 	tok->next = NULL;
// 	return tok;
// }

// t_token *tokenize(char *line)
// {
// 	t_token *head = NULL;
// 	t_token *tail = NULL;
// 	int i = 0;

// 	while (line[i])
// 	{
// 		// Pomijanie spacji
// 		while (line[i] && isspace(line[i]))
// 			i++;
// 		if (!line[i])
// 			break;

// 		t_token *tok = NULL;

// 		// PIPE
// 		if (line[i] == '|')
// 		{
// 			tok = new_token(PIPE, strdup("|"), NORMAL, FALSE);
// 			i++;
// 		}
// 		// REDIR
// 		else if (line[i] == '<' || line[i] == '>')
// 		{
// 			int start = i;
// 			i++;
// 			if (line[i] == line[start])
// 				i++; // obsługa << lub >>
// 			tok = new_token(REDIR, strndup(line + start, i - start), NORMAL, FALSE);
// 		}
// 		// WORD
// 		else
// 		{
// 			int state;
// 			int join;
// 			char *word = extract_word(line, &i, &state, &join);
// 			tok = new_token(WORD, word, state, join);
// 		}

// 		// Dodanie tokenu do listy
// 		if (!head)
// 			head = tok;
// 		else
// 			tail->next = tok;
// 		tail = tok;
// 	}

// 	return head;
// }

static int	get_quote_state(char c)
{
	if (c == '\'')
		return (SQ);
	if (c == '"')
		return (DQ);
	return (NORMAL);
}

static void	skip_quotes(char *line, int *i, int *state)
{
	char	quote;

	quote = line[*i];
	if (*state == NORMAL)
		*state = get_quote_state(quote);
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i])
		(*i)++;
}

static int	is_delimiter(char c)
{
	return (!c || isspace(c) || c == '|' || c == '<' || c == '>');
}

static char	*extract_word(char *line, int *i, int *state)
{
	int		start;
	char	*result;

	start = *i;
	*state = NORMAL;
	while (!is_delimiter(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			skip_quotes(line, i, state);
		else
			(*i)++;
	}
	result = strndup(line + start, *i - start);
	return (result);
}

static t_token	*new_token(int type, char *val, int state)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = val;
	tok->state = state;
	tok->next = NULL;
	return (tok);
}

static void	add_token(t_token **head, t_token **tail, t_token *tok)
{
	if (!*head)
		*head = tok;
	else
		(*tail)->next = tok;
	*tail = tok;
}

static t_token	*handle_redir(char *line, int *i)
{
	int		start;
	t_token	*tok;

	start = *i;
	(*i)++;
	if (line[*i] == line[start])
		(*i)++;
	tok = new_token(REDIR, strndup(line + start, *i - start), NORMAL);
	return (tok);
}

t_token	*tokenize(char *line)
{
	t_token	*head;
	t_token	*tail;
	t_token	*tok;
	int		i;
	int		state;

	head = NULL;
	tail = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|')
			tok = new_token(PIPE, strdup("|"), NORMAL);
		else if (line[i] == '<' || line[i] == '>')
			tok = handle_redir(line, &i);
		else
			tok = new_token(WORD, extract_word(line, &i, &state), state);
		if (line[i] == '|')
			i++;
		add_token(&head, &tail, tok);
	}
	return (head);
}

int main()
{
	char *line = "echo 'hello world' | grep \"foo\" > out.txt";
	t_token *tokens = tokenize(line);

	for (t_token *t = tokens; t; t = t->next)
	{
		printf("type=%d, value='%s', state=%d, join=%d\n",
			t->type, t->value, t->state, t->join);
	}

}
