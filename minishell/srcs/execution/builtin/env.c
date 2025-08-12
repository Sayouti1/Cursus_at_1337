/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:28:59 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:29:07 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

/*
 * APPENDING ENV[KEY=>VLAUE] TO THE LINKED LIST ENV ✅
 */
int	add_to_env(char *key, char *value, int to_export)
{
	t_env	*tmp;
	t_env	*new;

	if (key == NULL)
		return (free(key), 1);
	new = new_node(key, value, to_export);
	if (g_vars.env == NULL)
		g_vars.env = new;
	else
	{
		tmp = g_vars.env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

/*
 * INITIALIZING ENVIRMENT VARIABLES
 * ✅
 */
void	init_env(void)
{
	char	**split;
	int		i;

	i = 0;
	while (g_vars.envp && g_vars.envp[i])
	{
		split = split_on_two(g_vars.envp[i], "=");
		if (NULL == split)
			return ;
		add_to_env(ft_strdup(split[0]), ft_strdup(split[1] + 1), 1);
		free_split(split);
		i++;
	}
	fix_shlvl();
}

/*
 * RETURN A POINTER TO THE VALUE OF KEY FROM ENV
 * ✅
 */
char	*get_env_v1(char *key)
{
	t_env	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 * PRINT ENVIRONMENT VARIABLES ✅
 */
void	ft_env(void)
{
	t_env	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		if (tmp->value && tmp->to_export)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_vars.exit_status = 0;
}

/*
 * TO REPLACE VALUE OF AN EXISTING ENV[KEY, VALUE] ✅
 */
int	ft_env_replace(char *key, char *new_value)
{
	t_env	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			free(tmp->value);
			tmp->to_export = 1;
			tmp->value = ft_strdup(new_value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
