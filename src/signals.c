/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:16:57 by twatson           #+#    #+#             */
/*   Updated: 2026/01/14 11:36:12 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

/*	Core - Prompt - Children
	
		Before readline - set_signals_prompt();
   
    	before launching pipeline (parent) - set_signals_parent_running();

    	in each child just before exec - set_signals_child();

   		after waitpid - set_signals_prompt();
	
	Turning wait status into $?

	Heredoc Mode - ctrl-C abort heredoc, not shell
*/

static void signint_prompt(int signo)
{
	(void)signo;
	g_sig = 1;
	write(1, "\n", 1);
}

/* Signal can have 3 dipositions:
	SIG_DFL - kernel default behaviour
	SIG_IGN - kernel discards the signal
	Custom handler - own function called */

void	set_signals_prompt_mode(void)
{
	struct sigaction	sa;

	sa.sa_handler = signint_prompt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	return ;
}


