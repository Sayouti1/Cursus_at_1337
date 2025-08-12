/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:20:10 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 15:20:15 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	exec_echo(t_command *cmd)
{
	if (cmd->args)
		ft_echo(cmd->args);
	else
		ft_putstr_fd("\n", 1);
	g_vars.exit_status = 0;
}

void	exec_export(t_command *cmd)
{
	if (cmd->args)
		ft_export(cmd->args);
	else
		ft_print_export();
}

void	exec_env(t_command *cmd)
{
	if (NULL == cmd->args)
		ft_env();
	else
		g_vars.exit_status = 127;
}

void	exec_unset(t_command *cmd)
{
	if (cmd->args)
		ft_unset(cmd->args);
	g_vars.exit_status = 0;
}

void	execute_built_in(t_command *cmd, int piped)
{
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	update_under_s(cmd);
	if (!ft_strcmp(cmd->command, "echo"))
		exec_echo(cmd);
	else if (!ft_strcmp(cmd->command, "export"))
		exec_export(cmd);
	else if (!ft_strcmp(cmd->command, "unset"))
		exec_unset(cmd);
	else if (!ft_strcmp(cmd->command, "env"))
		exec_env(cmd);
	else if (!ft_strcmp(cmd->command, "cd"))
		exec_cd(cmd->args);
	else if (!ft_strcmp(cmd->command, "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->command, "exit"))
		ft_exit(cmd->args, piped);
}
