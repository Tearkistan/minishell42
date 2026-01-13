/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:16:57 by twatson           #+#    #+#             */
/*   Updated: 2026/01/13 15:43:33 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_ready = 0;

/*	Core - Prompt - Children
	
		Before readline - set_signals_prompt();
   
    	before launching pipeline (parent) - set_signals_parent_running();

    	in each child just before exec - set_signals_child();

   		after waitpid - set_signals_prompt();
	
	Turning wait status into $?

	Heredoc Mode - ctrl-C abort heredoc, not shell
*/




