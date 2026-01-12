/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnussler <mnussler@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:20:33 by mnussler          #+#    #+#             */
/*   Updated: 2025/09/20 16:20:34 by mnussler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Validates command line arguments for pipex
 * @param argc Argument count (must be 5)
 * @param argv Argument vector containing program name and parameters
 */
void	validate_args(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_printf("Usage: %s infile \"cmd1\" \"cmd2\" outfile\n", argv[0]);
		exit(2);
	}
}

/**
 * @brief Initializes pipex structure with files and commands
 * @param px Pipex structure to initialize
 * @param argv Command line arguments containing file and command names
 * @param envp Environment variables for command execution
 */
void	init_pipex(t_pipex *px, char **argv, char **envp)
{
	px->envp = envp;
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
	px->infile = open_input_file(argv[1]);
	px->outfile = open_output_file(argv[4]);
	parse_command(&px->cmd1, argv[2]);
	parse_command(&px->cmd2, argv[3]);
	resolve_command_path(&px->cmd1, envp);
	resolve_command_path(&px->cmd2, envp);
}

/**
 * @brief Main entry point for pipex program
 * @param argc Argument count
 * @param argv Argument vector: program infile "cmd1" "cmd2" outfile
 * @param envp Environment variables
 * @return Program exit status
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		exit_status;

	validate_args(argc, argv);
	init_pipex(&px, argv, envp);
	exit_status = execute_pipeline(&px);
	cleanup_pipex(&px);
	return (exit_status);
}
