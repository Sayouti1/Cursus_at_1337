/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:59 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:29:07 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	collect_garbage(void *to_add)
{
	t_garbage_collector	*tmp;

	tmp = malloc(sizeof(t_garbage_collector));
	tmp->str = to_add;
	tmp->next = g_vars.garbage_coll;
	g_vars.garbage_coll = tmp;
	return (0);
}

void	free_garbage(void)
{
	t_garbage_collector	*tmp;

	while (g_vars.garbage_coll)
	{
		tmp = g_vars.garbage_coll->next;
		free(g_vars.garbage_coll->str);
		g_vars.garbage_coll->str = NULL;
		free(g_vars.garbage_coll);
		g_vars.garbage_coll = tmp;
	}
	g_vars.garbage_coll = NULL;
}
