/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:20:46 by mnussler          #+#    #+#             */
/*   Updated: 2025/09/20 16:20:47 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	/** Split command string */
	char	**argv;
	/** Resolved absolute path */
	char	*path;
}			t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	t_cmd	cmd1;
	t_cmd	cmd2;
	/** Pipe file descriptors, 0 is read, 1 is write */
	int		pipe_fd[2];
	char	**envp;
}			t_pipex;

int			open_input_file(char *filename);
int			open_output_file(char *filename);
void		close_files(t_pipex *px);

void		parse_command(t_cmd *cmd, char *cmd_str);
void		resolve_command_path(t_cmd *cmd, char **envp);

int			execute_pipeline(t_pipex *px);

void		cleanup_pipex(t_pipex *px);
void		exit_error(char *msg, t_pipex *px);

#endif
