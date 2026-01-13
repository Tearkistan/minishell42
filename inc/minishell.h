/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:16:20 by twatson           #+#    #+#             */
/*   Updated: 2026/01/12 15:24:50 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

# define PROMPT "MINIsHELL$> "

/* For redirect type */
# define IN	0
# define HEREDOC 1
# define OUT 2
# define APPEND 3
# define FALSE 0
# define TRUE 1

/* NULL terminated linked list please */
typedef struct s_redirects
{	
	int					type;
	char				*target;
	int					quote_delim; // for heredoc only
	struct s_redirects	*next;
}	t_redirects;

/* per command with relevant args and redirects */
typedef struct s_cmd 
{
	char		**args;
	t_redirects	redirects;
}	t_cmd;

/* Null terminated Linked list please - pipeline per line with instance per pipe */
typedef struct s_pipeline
{
	t_cmd					cmd;
	struct s_pipeline		*next;
}	t_pipeline;

/* PARSING - Lexing + Parsing + Struct / Linked List Creation */
/* parse.c */
void	parse_line(t_pipeline *pipeline, char *line, char **envp);

/* EXECUTION - Main + Execution + Signalling */
/* main.c */
int		clean_up(void);

/* errors_main */
void	perror_exit(const char *label);

/* shell_init.c */
int 	shell_init(char **envp); //additional parameters TBD

/* shell_loop.c */
int		shell_loop(char **envp); // addtonal parameters TBD

/* execute.c */
void	execute_line(t_pipeline *pipeline, char **envp);

#endif
