/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:59 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:29:07 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

/*
 * ✅
 */
t_env	*new_node(char *key, char *value, int to_export)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (NULL == node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->to_export = to_export;
	node->next = NULL;
	return (node);
}

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		++i;
		env = env->next;
	}
	return (i);
}

char	**get_env_array(int i, char *key)
{
	char	**array;
	t_env	*env;

	env = g_vars.env;
	i = env_len(env);
	array = malloc(sizeof(char *) * (i + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (env)
	{
		if (ft_strcmp(env->key, "_") != 0)
		{
			if (NULL == env->value)
				key = ft_strjoin(env->key, "=");
			else
				key = ft_strjoin_prefixed(env->key, '=', env->value);
			collect_garbage(key);
			array[i++] = key;
		}
		env = env->next;
	}
	array[i] = NULL;
	collect_garbage(array);
	return (array);
}
