/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:16:20 by twatson           #+#    #+#             */
/*   Updated: 2026/03/19 18:40:51 by twatson          ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0

# define SUCCESS 1
# define FAILURE 0

# define EXIT_SUCCESS 0
# define EXIT_FAILUE 1

# define NUL 0
# define SQ 39
# define DQ 34
# define PIPE 124

# define P "\033[95m" // Purple
# define G "\033[92m" // Green
# define Y "\033[93m" // Yellow
# define RD "\033[91m" // Red
# define R "\033[0m" // Reset color

# define ERR_MEMORY "Error: memory allocation failed\n"
# define ERR_UNCLOSED_QUOTE "Syntax error: unclosed quote\n"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIR,
	TOKEN_PIPE
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_redir_type
{
	REDIR_IN, //<
	REDIR_OUT, //>
	HEREDOC, //<<
	REDIR_APP, //>>
}	t_redir_type;

/* NULL terminated linked list please */
typedef struct s_redirects
{
	t_redir_type		type;
	char				*target;
	int					quote_delim;
	struct s_redirects	*next;
}	t_redirects;

/* per command with relevant args and redirects */
typedef struct s_cmd
{
	char		**args;
	t_redirects	*redirects;
}	t_cmd;

/* pipeline per line with instance per pipe */
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
	int		running;
	int		envp_len;
	char	**no_eq;
}	t_shell;

/* Pipex struct for execution */
typedef struct s_pipe
{
	int		hd_fd;
	int		hd_pipe[2];
	int		in_fd;
	int		out_fd;
	int		prev_read_fd;
	int		pipe_fd[2];
	int		cmd_count;
	int		n_spawned;
	pid_t	last_pid;
	int		*pids;
}	t_pipe;

typedef struct s_export
{
	char	**temp_envp;
	char	*new_line;
	char	*key;
	char	*value;
	int		arg_count;
	int		parent;
	int		append;
	int		eq;
	int		close_quote;
}	t_export;

typedef struct s_unset
{
	char	**new_envp;
	int		new_len;
	char	**valid_args;
	char	**sorted_args;
	int		arg_count;
	int		valid_count;
	int		parent;
}	t_unset;

typedef struct s_cd
{
	char	*old_pwd;
	char	*new_pwd;
	int		path_check;
	int		arg_count;
	int		parent;
}	t_cd;

extern volatile sig_atomic_t	g_sig;

/* PARSING - Lexing + Parsing + Struct / Linked List Creation */
// FREE.c
void		free_tokens(t_token *tokens);
void		free_args(char **args);
void		free_redirects(t_redirects *redir);
void		free_pipeline(t_pipeline *pipeline);

// PRINT.c DEBUGGING
void		print_envp(char **envp);
void		print_tokens(t_token *tokens);
void		print_pipeline(t_pipeline *pipeline);

// ERROR.c
void		error_msg(char *message);

// parsing utils
char		*char_to_str(char c);
char		*ft_strjoin_free(char *s1, char *s2);
int			has_quotes(const char *str);
int			is_redir(char c);
int			is_special(char c);
char		skip_whitespaces(char *line, int *index);

// parse_line.c
t_pipeline	*parse_line(char *line, t_shell shell);

// parse_word.c
char		*parse_word(char *word, t_shell shell, int expand);
char		*expand_env(char *line, int *index, t_shell shell);

// tokenize
t_token		*tokenize_line(char *line);
int			add_token_back(t_token **tokens, t_token *new_token);
int			add_token_pipe(t_token **tokens);
int			add_token_redir(t_token **tokens, char *line, int *index);
int			add_token_word(t_token **tokens, char *line, int *index);
int			check_token_syntax(t_token *tokens);

// create pipeline from tokens
t_pipeline	*create_pipeline_from_tokens(t_token *tokens, t_shell shell);
t_pipeline	*empty_pipeline(void);
int			add_arg(t_pipeline *current, t_token token, t_shell shell);
int			add_pipe(t_pipeline **current);
int			add_redir(t_pipeline *current, t_token **token, t_shell shell);

/* EXECUTION - Main + Execution + Signalling */

/* errors_main */
void		perror_exit(const char *label);
void		msg_exit(char *msg);

/* shell_init.c */
char		**copy_envp(char **copy, char **original, int allocate);
void		shell_init(t_shell *shell, char **envp);

/* shell_loop.c */
void		shell_loop(t_shell *shell);

/* clean.c */
void		free_matrix(char **dir);
void		clean_up(t_shell *sh, t_pipeline *pl, char *line, char *err_msg);
void		clean_exit_child(t_pipe *pipex, t_pipeline *head, t_shell *shell);

/* execute.c */
void		exec_cmd(char **cmd_args, char **envp);
int			execute_line(t_pipeline *pipeline, t_shell *shell);

/* execute_utils.c */
int			contains_path(char *cmd);
void		path_check_to_execute(char **cmd_args, char *cmd, char **envp);

/* exec_stateful.c */
int			exec_stateful_builtin(t_pipeline *pline, t_shell *sh);

/* exec_pipeline.c */
int			is_stateful(char *cmd);
int			is_nonstateful(char *cmd);
int			exec_pipeline(t_pipeline *pipeline, t_shell *sh, t_pipe *pipex);
int			pipeline_size(t_pipeline *p);

/* exec_errors.c */
void		permission_denied_exit(char **cmd_args);
void		not_found_exit(char **cmd_args);
int			perror_int(char *err_msg, int n);
int			abort_pipeline_parent(t_pipe *pipex, t_shell *shell, int stat_code);
int			write_pipe_exit(int pipe[2], char *s, int n);

/* heredoc */
int			count_heredoc(t_redirects *redir);
int			init_heredoc_mode(t_pipe *pipex, t_redirects *redir, t_shell *sh);
int			heredoc_read(t_redirects *redir, t_pipe *pipex, t_shell *shell);

/* redirects.c */
void		set_in_fd(t_redirects *redir, t_pipe *pipex);
void		set_out_fd(t_redirects *redir, t_pipe *pipex);
void		infile_guard(t_pipe *pipex);
void		close_pipe(int pipe[2]);

/* path.c */
char		*find_path(char **cmds, char *cmd, char **envp);
char		*find_cmd(char **dirs, char **cmd_args, char *arg);
char		*get_env_path(char **envp);
char		*join_paths(char *dir, char *cmd);

/* builtin.c */
int			is_builtin(char *cmd);
int			append_shell_envp(t_shell *shell, char *new_line);
int			ft_strncmp_set(char *str, char **set);
char		**copy_array(char **set);
int			builtin_exec(char **cmd_args, t_shell *shell, int parent);

/* builtin_utils.c */
char		*shell_getenv(char *key, t_shell *sh);

/* exec_echo.c */
int			exec_echo(char **cmd_args);

/* exec_env.c */
int			exec_env(char **cmd_args, char **envp);

/* exec_pwd.c */
int			exec_pwd(char **cmd_args);

/* cd.c */
int			exec_cd_ctrl(char **cmd_args, t_shell *shell, int parent);

/* exit.c */
int			exec_exit(char **cmd_args, t_shell *shell, int parent);

/* unset.c */
void		exit_unset(t_unset *unset, t_shell *shell, int alloc_fail);
void		get_valid_args(char **cmd_args, t_unset *unset, t_shell *shell);
int			exec_unset_ctrl(char **cmd_args, t_shell *shell, int parent);

/* unset_utils.c */
void		resize_unset_envp(t_unset *unset, t_shell *shell);
void		rm_duplicate_args(t_unset *unset, t_shell *shell);
void		remove_valid_args(t_shell *shell, t_unset *unset);

/* unset_utils_plus.c */
int			add_unique_to_array(t_unset *unset);

/* export.c */
void		exit_export(t_export *export, t_shell *shell, int alloc_fail);
int			exec_export_ctrl(char **cmd_args, t_shell *shell, int parent);

/* export_utils.c */
void		print_export(char **envp, char **no_eq);
int			export_arg_error(char *cmd_arg, t_export *export);
int			find_var_in_env(char **envp, char *key);
char		*create_line(char *key, char *value);
void		alloc_key_value(char *arg, t_export *export, t_shell *shell);

/* export_utils_plus.c */
int			is_no_eq(char *var, char **no_eq);
void		add_no_equal_key(t_export *export, t_shell *shell);
void		finish_export_arg(t_shell *shell, t_export *export, int index);

/* signals.c */
void		set_signals_prompt_mode(void);
void		set_signals_child(void);
void		set_signals_parent_running(void);
void		signint_heredoc(int signo);

/* signals_utils.c */
void		set_signals_heredoc(void);
void		resolve_prompt_sigint(t_shell *shell);
void		resolve_heredoc_sigint(char *line, t_shell *shell, t_pipe *pipex);
int			status_to_exitcode(int status);
int			ft_strncmp_set(char *str, char **set);

#endif
