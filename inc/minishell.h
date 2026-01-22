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
# include <signal.h>

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
	t_cmd				cmd;
	struct s_pipeline	*next;
}	t_pipeline;

/* Shell struct w/ envp, last status, running */
typedef struct s_shell
{
	char	**envp;
	int		last_status;
}	t_shell;

/* Pipex struct for execution */
typedef struct s_pipe
{
	int		hd_fd;
	int		hd_pipe[2];
	int		in_fd;
	int		out_fd;
	int 	prev_read_fd;
	int 	pipe_fd[2];
	int		cmd_count;
	int		n_spawned;
	pid_t	last_pid;
	int		*pids;
}	t_pipe;

extern volatile sig_atomic_t	g_sig;

/* PARSING - Lexing + Parsing + Struct / Linked List Creation */
/* parse.c */
int		parse_line(t_pipeline *pipeline, char *line, t_shell *shell);

/* EXECUTION - Main + Execution + Signalling */

/* errors_main */
void	perror_exit(const char *label);
void	msg_exit(char *msg);

/* shell_init.c */
void	shell_init(t_shell *shell, char **envp); //additional parameters TBD

/* shell_loop.c */
void	shell_loop(t_shell *shell); // addtonal parameters TBD

/* clean.c */
void	free_matrix(char **dir);
void	clean_up(t_shell *sh, t_pipeline *pipeline, char *line, char *err_msg);

/* execute.c */
void	exec_cmd(char **cmd_args, char **envp);
int		execute_line(t_pipeline *pipeline, t_shell *shell);

/* exec_stateful.c */
int		exec_stateful_builtin(t_pipeline *pline, t_shell *sh, t_pipe *pipex);

/* exec_pipeline.c */
int		exec_pipeline(t_pipeline *s_pipeline, t_shell *sh, t_pipe *pipex);
int		pipeline_size(t_pipeline *p);

/* exec_errors.c */
void	permission_denied_exit(char **cmd_args);
void	not_found_exit(char **cmd_args);
int		perror_int(char *err_msg, int n);
int		abort_pipeline_parent(t_pipe *pipex, t_shell *shell, int status_code);
int		write_pipe_exit(int pipe[2], char *s, int n);

/* heredoc */
int		count_heredoc(t_redirects *redir);
int		init_heredoc_mode(t_pipe *pipex, t_redirects *redir, t_shell *shell);
int		heredoc_read(t_redirects *redir, t_pipe *pipex, t_shell *shell);

/* redirects.c */
void    set_in_fd(t_redirects *redir, t_pipe *pipex);
void    set_out_fd(t_redirects *redir, t_pipe *pipex);
void	infile_guard(t_pipe *pipex);

/* path.c */
char	*find_path(char **cmds, char *cmd, char **envp);
char	*find_cmd(char **dirs, char **cmd_args, char *arg);
char	*get_env_path(char **envp);
char	*join_paths(char *dir, char *cmd);

/* signals.c */
void	set_signals_prompt_mode(void);
void	set_signals_child(void);
void	set_signals_parent_running(void);
void	signint_heredoc(int signo);

/* signals_utils.c */
void	set_signals_heredoc(void);
void	resolve_prompt_sigint(t_shell *shell);
void	resolve_heredoc_sigint(char *line, t_shell *shell, t_pipe *pipex);
int		status_to_exitcode(int status);

#endif
