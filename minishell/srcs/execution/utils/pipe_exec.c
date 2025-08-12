/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:20:12 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	not_first_command(t_command *cmd, int prev_in)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	cmd->fd_in = prev_in;
}

void	not_last_command(t_command *cmd, int curr_out)
{
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	cmd->fd_out = curr_out;
}

int	init_commands_fds(t_command *cmd, int len, int *curr_pipes, int *prev_pipes)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (i != 0)
			swap_pipes(curr_pipes, prev_pipes);
		if (i < len - 1 && pipe(curr_pipes))
			return (perror("minishell "), 1);
		add_to_fds(curr_pipes[0]);
		add_to_fds(curr_pipes[1]);
		if (i != 0)
			not_first_command(cmd, prev_pipes[0]);
		if (i != len - 1)
			not_last_command(cmd, curr_pipes[1]);
		redirection_exec(cmd);
		++i;
		cmd = cmd->next;
	}
	return (0);
}

int	execute_pipes(int len, int i, t_command *cmd, int *pids)
{
	int			curr_pipes[2];
	int			prev_pipes[2];
	int			pid;

	init_commands_fds(cmd, len, curr_pipes, prev_pipes);
	i = 0;
	while (cmd)
	{
		g_vars.parent = 0;
		pid = fork();
		signal(SIGQUIT, sig_handler);
		if (pid == 0)
		{
			execute_command(cmd, 1);
			close_file_ds();
			free_cmd_token_garbage();
			exit(g_vars.exit_status);
		}
		pids[i] = pid;
		close_fds(cmd);
		cmd = cmd->next;
		i++;
	}
	close_file_ds();
	return (0);
}

void	process_command(t_command *command)
{
	t_command	*tmp_cmd;
	pid_t		*pids;
	int			i;
	int			j;

	if (list_len(command) == 1)
		execute_command(command, 0);
	else
	{
		i = list_len(command);
		pids = malloc(sizeof(int) * (i));
		collect_garbage(pids);
		if (NULL == pids && printf("Error Allocating pids\n"))
			return ;
		tmp_cmd = command;
		execute_pipes(i, i, tmp_cmd, pids);
		j = 0;
		while (j < i)
		{
			waitpid(pids[j++], &g_vars.exit_status, 0);
			if (j == i)
				set_exit_status(g_vars.exit_status);
		}
		g_vars.parent = 1;
	}
}
