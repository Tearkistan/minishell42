/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:16:20 by twatson           #+#    #+#             */
/*   Updated: 2026/01/16 18:34:32 by twatson          ###   ########.fr       */
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

/* Shell struct w/ envp, last status, running */
typedef struct s_shell
{
	char	**envp;
	int		last_status;
}	t_shell;

/* Pipex struct for execution */
typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int 	prev_fd;
	int 	pipe_fd[2];
	int		cmd_count; 
	pid_t	last_pid;
}	t_pipex;

extern volatile sig_atomic_t	g_sig;

/* PARSING - Lexing + Parsing + Struct / Linked List Creation */
/* parse.c */
int		parse_line(t_pipeline *pipeline, char *line, t_shell *shell);

/* EXECUTION - Main + Execution + Signalling */

/* errors_main */
void	perror_exit(const char *label);

/* shell_init.c */
void	shell_init(t_shell *shell, char **envp); //additional parameters TBD

/* shell_loop.c */
void	shell_loop(t_shell *shell); // addtonal parameters TBD

/* clean.c */
void	clean_up(t_shell *sh, t_pipeline *pipeline, char *line, char *err_msg);

/* execute.c */
int		execute_line(t_pipeline *pipeline, t_shell *shell);

/* heredoc.c */
int		heredoc_read(t_redirects *redir, t_pipex *pipex, t_shell *shell);

/* signals.c */
void	set_signals_prompt_mode(void);
void	set_signals_child(void);
void	set_signals_parent_running(void);
void	signint_heredoc(int signo);

/* signals_utils.c */
void	set_signals_heredoc(void);
void	resolve_prompt_sigint(t_shell *shell);
void	resolve_heredoc_sigint(char *line, t_shell *shell, t_pipex *pipex);

#endif
