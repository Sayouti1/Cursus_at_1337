/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:05:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/23 13:51:38 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_vars	g_vars;

void	print_and_exit(char *str, int code)
{
	ft_putstr_fd(str, 1);
	exit(code);
}

void	send_char(char c, int spid)
{
	while (g_vars.shift <= 7)
	{
		g_vars.wait = 0;
		if ((c >> g_vars.shift) & 1)
		{
			if (kill(spid, SIGUSR1) == -1)
				print_and_exit("\nUnable to send to PID!", 1);
		}
		else
		{
			if (kill(spid, SIGUSR2) == -1)
				print_and_exit("\nUnable to send to PID!", 1);
		}
		g_vars.shift++;
		while (!g_vars.wait)
		{
			sleep(3);
			if (!g_vars.wait)
				print_and_exit("\nTimeout, Unable to reach the server!", 1);
		}
	}
	g_vars.shift = 0;
}

void	ft_ok(int sig)
{
	if (sig == SIGUSR2)
		print_and_exit("\nMessage sent successfully!\n", 0);
	else if (sig == SIGUSR1)
		g_vars.wait = 1;
}

int	main(int ac, char **av)
{
	int	spid;
	int	i;

	if (ac != 3)
		return (1);
	if (!is_valid_pid(av[1]) || ft_atoi(av[1]) < 0)
		return (ft_putstr_fd("PID is not valid!!", 1), 1);
	spid = ft_atoi(av[1]);
	g_vars.sa.sa_handler = ft_ok;
	g_vars.sa.sa_flags = 0;
	signal(SIGINT, ft_wait);
	sigaction(SIGUSR2, &g_vars.sa, NULL);
	sigaction(SIGUSR1, &g_vars.sa, NULL);
	i = 0;
	while (av[2][i])
		send_char(av[2][i++], spid);
	if (!av[2][i])
		send_char(av[2][i], spid);
	while (!g_vars.stop)
		sleep(1);
	return (0);
}
