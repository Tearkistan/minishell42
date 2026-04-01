/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:16:57 by twatson           #+#    #+#             */
/*   Updated: 2026/03/30 13:34:14 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

static int	prompt_event_hook(void)
{
	if (g_sig != SIGINT)
		return (0);
	ft_putstr_fd("^C", 1);
	rl_replace_line("", 0);
	rl_done = 1;
	return (0);
}

static void	signint_prompt(int signo)
{
	g_sig = signo;
}

void	set_signals_prompt_mode(void)
{
	struct sigaction	sa;

	sa.sa_handler = signint_prompt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = prompt_event_hook;
	return ;
}
