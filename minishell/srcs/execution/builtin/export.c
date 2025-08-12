/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:29:37 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:29:39 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	ft_concat_env_var(char *var, char *tmp, int i, int x)
{
	char	**key_value;

	i = 0;
	while (var && var[i] && var[i] != '=')
		++i;
	if (i < 2 || !var[i] || var[i - 1] != '+')
		return (0);
	if (var[i] == '=' && (!ft_isalnum(var[i - 1]) && var[i - 1] != '+'
			&& var[i - 1] != '_'))
		return (ft_perror("export: `", var, "': not a valid identifier\n"),
			g_vars.exit_status = 1, 1);
	key_value = split_on_two(var, "+");
	if (NULL == key_value)
		return (g_vars.exit_status = 1, 1);
	x = 0;
	if (key_value[1])
		x = 2;
	tmp = string_concat(ft_strdup(get_env_v1(key_value[0])),
			ft_strdup(key_value[1] + x));
	if (!ft_env_replace(key_value[0], tmp))
		add_to_env(ft_strdup(key_value[0]), tmp, 1);
	else
		free(tmp);
	free_split(key_value);
	return (1);
}

int	is_not_valid(char *var)
{
	int	i;
	int	j;

	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (ft_perror("export: `", var, "': not a valid identifier\n"),
			g_vars.exit_status = 1, 1);
	j = 0;
	while (var[j] && var[j] != '=')
		++j;
	i = 0;
	while (++i < j)
	{
		if (i == j - 1 && var[i] == '+')
			break ;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (ft_perror("export: `", var, "': not a valid identifier\n"),
				g_vars.exit_status = 1, 1);
	}
	return (0);
}

int	ft_export(char **var)
{
	char	**key_value;
	int		i;
	int		x;

	i = 0;
	while (var && var[i])
	{
		if (is_not_valid(var[i]) && ++i)
			continue ;
		if (ft_concat_env_var(var[i], NULL, 0, 0) && ++i)
			continue ;
		key_value = split_on_two(var[i++], "=");
		if (NULL == key_value)
			return (g_vars.exit_status = 1, 1);
		x = 0;
		if (key_value[1])
			x = 1;
		if (!ft_env_replace(key_value[0], key_value[1] + x))
			add_to_env(ft_strdup(key_value[0]), ft_strdup(key_value[1] + x),
				ft_char_in('=', var[i - 1]));
		free_split(key_value);
		g_vars.exit_status = 0;
	}
	return (0);
}

void	ft_print_export(void)
{
	t_env	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") != 0)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
	g_vars.exit_status = 0;
}
