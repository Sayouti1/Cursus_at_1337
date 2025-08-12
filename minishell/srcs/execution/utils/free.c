/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:53 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	free_env(void)
{
	t_env	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		g_vars.env = g_vars.env->next;
		free(tmp);
		tmp = g_vars.env;
	}
	g_vars.env = NULL;
}

void	delete_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	free_split(char **arr)
{
	int	i;

	if (NULL == arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	reset_fd(void)
{
	dup2(g_vars.std_out, 1);
	dup2(g_vars.std_in, 0);
	return (1);
}

void	free_cmds(t_command *cmd)
{
	t_command		*tmp;
	t_redirection	*tmp_red;

	tmp = NULL;
	while (cmd)
	{
		tmp = cmd->next;
		while (cmd->redirection)
		{
			tmp_red = cmd->redirection->next;
			free_redirection(cmd->redirection);
			cmd->redirection = tmp_red;
		}
		if (cmd->fd_in != 0 && cmd->fd_in > 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1 && cmd->fd_out > 0)
			close(cmd->fd_out);
		free(cmd->command);
		free_split(cmd->args);
		free(cmd);
		cmd = tmp;
	}
	reset_fd();
}
