/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:53 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	free_redirection(t_redirection *red)
{
	if (red->fd >= 0)
		close(red->fd);
	free(red->file_name);
	free(red);
}

void	free_cmd_token_garbage(void)
{
	free_cmds(g_vars.cmd);
	g_vars.cmd = NULL;
	free_token(g_vars.token);
	free_env();
	free_garbage();
}
