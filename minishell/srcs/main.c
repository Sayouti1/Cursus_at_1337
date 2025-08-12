/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:29:04 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:30:17 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

t_global_vars	g_vars;

void	init_g_vars(char **envp)
{
	g_vars.env = NULL;
	g_vars.envp = envp;
	g_vars.exit_status = 0;
	g_vars.sig_c = 0;
	g_vars.tmp_file = 0;
	g_vars.parent = 1;
	g_vars.fd_collectors = NULL;
	g_vars.std_in = dup(0);
	g_vars.std_out = dup(1);
	g_vars.garbage_coll = NULL;
}

void	main_loop(void)
{
	char	*line;

	while (1)
	{
		g_vars.cmd = NULL;
		g_vars.token = NULL;
		sig_init();
		line = readline("minishell :)=> ");
		if (!line)
			break ;
		if (!check_line(&line))
		{
			add_history(line);
			process_line(line, &g_vars.cmd);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	init_g_vars(envp);
	init_env();
	main_loop();
	rl_clear_history();
	free_env();
	close(g_vars.std_in);
	close(g_vars.std_out);
	exit(g_vars.exit_status);
}
