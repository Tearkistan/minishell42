/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:20:07 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/29 10:54:28 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

static volatile sig_atomic_t	g_status = 0;

static void	ft_acknowledgment(int signum)
{
	if (signum == SIGUSR1)
		g_status = 1;
	else if (signum == SIGUSR2)
		g_status = 2;
}

int	ft_send_byte(pid_t pid, int byte)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_status = 0;
		if (1 & (byte >> bit))
		{
			if (kill(pid, SIGUSR1) == -1)
				return (-1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (-1);
		}
		while (!g_status)
			pause();
		bit++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int					pid;
	unsigned char		*message;
	struct sigaction	sa;

	if (ac != 3 || !ft_isalldigits(av[1]) || ft_atoi(av[1]) == 0)
		return (ft_printf("Error: arguments\n"), -1);
	pid = ft_atoi(av[1]);
	message = (unsigned char *)av[2];
	sa.sa_handler = ft_acknowledgment;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (*message)
	{
		if (ft_send_byte(pid, *message) == -1)
			return (ft_printf("Error: sending process\n"), -1);
		message++;
	}
	if (ft_send_byte(pid, '\0') == -1)
		return (ft_printf("Error: sending process\n"), -1);
	if (g_status == 2)
		ft_printf("Whole message was received by server\n");
	return (0);
}
