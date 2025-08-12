/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:30:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:30:53 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	search_and_delete(t_env *iter, char *split)
{
	t_env	*tmp;

	if (iter && !ft_strcmp(iter->key, split))
	{
		g_vars.env = iter->next;
		delete_env(iter);
		return ;
	}
	while (iter)
	{
		if (iter->next && !ft_strcmp(iter->next->key, split))
			break ;
		iter = iter->next;
	}
	if (NULL == iter)
		return ;
	tmp = iter->next;
	iter->next = iter->next->next;
	delete_env(tmp);
}

int	ft_unset(char **key)
{
	t_env	*iter;
	int		i;

	i = 0;
	while (key && key[i])
	{
		iter = g_vars.env;
		search_and_delete(iter, key[i++]);
	}
	return (0);
}
