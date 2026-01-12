/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twatson <twatson@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:42:22 by twatson           #+#    #+#             */
/*   Updated: 2026/01/12 13:40:25 by twatson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int shell_init(char **envp)
{
	(void) envp;
	return (0); 
	// setup shell state (envp copy, last exit status...)
	// set signal handlers for prompt mode
}
