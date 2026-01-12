/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:16:20 by twatson           #+#    #+#             */
/*   Updated: 2026/01/12 14:12:16 by twatson          ###   ########.fr       */
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

/* linked list? if so NULL terminated please */
/* in this case a char **cmd would probably simplier */
typedef struct s_cmd //
{
	char	*arg;
	void	*PLACE_HOLDER; // + linked list fields
}	t_cmd;

/* linked list? if so NULL terminated please */
typedef struct s_redirects
{	
	int		type;
	char	*target;
	int		quote_delim; // for heredoc only
	void 	*PLACE_HOLDER; // + linked list fields
}	t_redirects;

/* pipe per command with relevant args and redirects */
typedef struct s_pipe 
{
	t_cmd		cmd; // char** probably simpler command composed of args / tokens
	t_redirects	redirects;
	int			first; // true / false
	int			last; // ture / false
}	t_pipe;


/* PARSING - Lexing + Parsing + Struct / Linked List Creation */


/* EXECUTION - Main + Execution + Signalling */
/* main.c */
int		clean_up(void);

/* errors_main */
void	perror_exit(const char *label);

/* shell_init.c */
int 	shell_init(char **envp); //additional parameters TBD

/* shell_loop.c */
int		shell_loop(char **envp); // addtonal parameters TBD

#endif
