/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:20:12 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	fd_in_list(int fd)
{
	t_fd_collectors	*tmp;

	tmp = g_vars.fd_collectors;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	add_to_fds(int val)
{
	t_fd_collectors	*node;
	t_fd_collectors	*tmp;

	if (fd_in_list(val))
		return ;
	node = malloc(sizeof(t_fd_collectors));
	if (NULL == node)
		return ;
	node->fd = val;
	node->next = NULL;
	if (NULL == g_vars.fd_collectors)
		g_vars.fd_collectors = node;
	else
	{
		tmp = g_vars.fd_collectors;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	close_file_ds(void)
{
	t_fd_collectors	*tmp;

	while (g_vars.fd_collectors)
	{
		tmp = g_vars.fd_collectors->next;
		if (g_vars.fd_collectors->fd != -1)
			close(g_vars.fd_collectors->fd);
		free(g_vars.fd_collectors);
		g_vars.fd_collectors = tmp;
	}
	if (g_vars.parent == 0)
	{
		if (g_vars.std_in != -1)
			close(g_vars.std_in);
		if (g_vars.std_out != -1)
			close(g_vars.std_out);
	}
	g_vars.fd_collectors = NULL;
}

void	close_fds(t_command *cmd)
{
	if (cmd->prev)
	{
		close(cmd->prev->fd_out);
		if (cmd->prev->fd_in != 0)
			close(cmd->prev->fd_in);
	}
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
}

void	swap_pipes(int *curr_pipes, int *prev_pipes)
{
	prev_pipes[0] = curr_pipes[0];
	prev_pipes[1] = curr_pipes[1];
}
