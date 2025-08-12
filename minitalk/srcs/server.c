/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:56:18 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/22 00:00:00 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_vars	g_vars;

void	ft_handler(int signum, siginfo_t *info, void *context)
{
	if (signum == SIGUSR1)
		g_vars.byte = g_vars.byte + (1 << g_vars.shift);
	g_vars.shift++;
	if (g_vars.shift == 8)
	{
		ft_putchar_fd(g_vars.byte, 1);
		if (g_vars.byte == '\0')
			ft_putchar_fd('\n', 1);
		g_vars.byte = 0;
		g_vars.shift = 0;
	}
	kill((int)info->si_pid, SIGUSR1);
	(void)context;
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	g_vars.sa.sa_flags = SA_SIGINFO;
	g_vars.sa.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &g_vars.sa, NULL);
	sigaction(SIGUSR2, &g_vars.sa, NULL);
	while (1)
		sleep(1);
	return (0);
}
