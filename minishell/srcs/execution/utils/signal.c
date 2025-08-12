/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:34:46 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_vars.exit_status = 130;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (g_vars.parent)
			rl_redisplay();
	}
	if (sig == SIGQUIT)
		printf("Quit (core dumped)\n");
}

void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_vars.sig_c = 1;
		g_vars.exit_status = 130;
		ft_putchar_fd('\n', 1);
		close(STDIN_FILENO);
	}
}

void	sig_init(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	g_vars.sig_c = 0;
}
