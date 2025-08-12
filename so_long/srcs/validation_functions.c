/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:02:44 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/02/06 18:02:48 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_ext(char *path)
{
	int		len;
	char	*sub;

	len = ft_strlen_gnl(path);
	if (len <= 4)
		return (0);
	sub = ft_strnstr(path + len - 5, ".ber", 5);
	if (!sub || sub[4])
		return (0);
	return (1);
}

int	is_rectangular(t_vars vars)
{
	int	height;
	int	i;
	int	len;

	height = get_map_height(vars.map);
	len = ft_strlen_gnl(vars.map[0]);
	i = 1;
	while (i < height)
	{
		if (len != ft_strlen_gnl(vars.map[i]))
			return (0);
		++i;
	}
	return (1);
}

int	is_surrounded(t_vars vars)
{
	int	i;
	int	len;

	i = 0;
	while (vars.map && vars.map[0] && vars.map[0][i])
		if (vars.map[0][i++] != '1')
			return (0);
	i = 0;
	len = get_map_height(vars.map) - 1;
	while (vars.map && vars.map[len] && vars.map[len][i])
		if (vars.map[len][i++] != '1')
			return (0);
	while (len-- > 0)
	{
		i = 0;
		while (vars.map && vars.map[len][i])
		{
			if ((i == 0 || i == ft_strlen_gnl(vars.map[len]) - 1)
				&& vars.map[len][i] != '1')
				return (0);
			i++;
		}
	}
	return (1);
}

int	is_valid_path_to_exit(t_vars *vars)
{
	int		collectible;
	int		player_x;
	int		player_y;
	char	**copy_map;

	copy_map = get_copy_map(*vars);
	if (!copy_map)
		return (0);
	player_x = get_player_x(*vars);
	player_y = get_player_y(*vars);
	collectible = vars->map_s.c;
	flood_fill_collectible(vars, copy_map, player_x, player_y);
	if (vars->map_s.c != 0)
		return (free_arr(copy_map) != 0);
	vars->map_s.c = collectible;
	if (flood_fill_exit(*vars, copy_map, player_x, player_y) == 0)
		return (free_arr(copy_map) != 0);
	free_arr(copy_map);
	return (1);
}
