/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:27 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:18:48 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	dup2_and_close(int new_fd, int old_fd)
{
	dup2(new_fd, old_fd);
	close(new_fd);
}

int	execute_bin(t_command *cmd)
{
	int		pid;

	g_vars.parent = 0;
	pid = fork();
	signal(SIGQUIT, sig_handler);
	if (0 == pid)
	{
		if (cmd->fd_in != 0)
			dup2_and_close(cmd->fd_in, 0);
		if (cmd->fd_out != 1)
			dup2_and_close(cmd->fd_out, 1);
		close_file_ds();
		execve(cmd->command, cmd->args, get_env_array(0, NULL));
		perror("minishell ");
		if (errno == EACCES || errno == EISDIR)
			g_vars.exit_status = 126;
		if (errno == ENOENT)
			g_vars.exit_status = 127;
		free_cmd_token_garbage();
		exit(g_vars.exit_status);
	}
	wait(&g_vars.exit_status);
	g_vars.parent = 1;
	return (set_exit_status(g_vars.exit_status), 0);
}

int	execute_bin_pipe(t_command *cmd)
{
	if (cmd->fd_in != 0)
		dup2_and_close(cmd->fd_in, 0);
	if (cmd->fd_out != 1)
		dup2_and_close(cmd->fd_out, 1);
	close_file_ds();
	execve(cmd->command, cmd->args, get_env_array(0, NULL));
	perror("minishell ");
	if (errno == EACCES || errno == EISDIR)
		g_vars.exit_status = 126;
	if (errno == ENOENT)
		g_vars.exit_status = 127;
	return (g_vars.exit_status);
}

void	redirection_exec(t_command *cmd)
{
	t_redirection	*tmp;

	tmp = cmd->redirection;
	while (tmp)
	{
		if (tmp->type == OUTPUT || tmp->type == APPEND)
			cmd->fd_out = tmp->fd;
		else if (tmp->type == INPUT)
			cmd->fd_in = tmp->fd;
		else if (tmp->type == HEREDOC && 0 == open_heredoc(tmp, NULL, NULL))
			cmd->fd_in = tmp->fd;
		tmp = tmp->next;
	}
}

void	execute_command(t_command *cmd, int piped)
{
	if (!piped)
		redirection_exec(cmd);
	if (g_vars.sig_c == 2 || check_redirection(cmd))
		return ;
	if (built_in(cmd->command))
		execute_built_in(cmd, piped);
	else
	{
		if (NULL == cmd->command)
			g_vars.exit_status = 0;
		else if (fix_command_path(cmd))
			g_vars.exit_status = 127;
		else if (NULL == get_env_v1("PATH") && NULL == cmd->command)
			ft_perror(cmd->command, ": No such file or directory\n", NULL);
		else
		{
			if (is_directory(cmd->command)
				&& ft_perror("minishell ", cmd->command, ": Is a directory\n"))
				g_vars.exit_status = 126;
			else if (piped)
				execute_bin_pipe(cmd);
			else
				execute_bin(cmd);
		}
	}
}
