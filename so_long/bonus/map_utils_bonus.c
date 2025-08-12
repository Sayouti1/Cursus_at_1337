/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:03:34 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/02/06 18:03:35 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	get_player_x(t_vars vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars.map && vars.map[i])
	{
		j = 0;
		while (vars.map[i][j])
		{
			if (vars.map[i][j] == 'P')
				return (j);
			++j;
		}
		++i;
	}
	return (0);
}

int	get_player_y(t_vars vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars.map && vars.map[i])
	{
		j = 0;
		while (vars.map[i][j])
		{
			if (vars.map[i][j] == 'P')
				return (i);
			++j;
		}
		++i;
	}
	return (0);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		++i;
	return (i);
}

char	**get_copy_map(t_vars vars)
{
	char	**copy_map;
	int		i;

	copy_map = (char **)malloc(sizeof(char *) * (vars.map_s.height + 1));
	if (!copy_map)
		return (NULL);
	i = 0;
	while (i < vars.map_s.height)
	{
		copy_map[i] = ft_strdup(vars.map[i]);
		if (!copy_map[i])
			return (free_arr(copy_map));
		++i;
	}
	copy_map[i] = NULL;
	return (copy_map);
}

void	display_image_at(t_vars *vars, int i, int j)
{
	if (vars->map[i][j] == '1')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->map_s.imgs.w_img, j
			* 50, i * 50);
	if (vars->map[i][j] == 'C')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->map_s.imgs.c_img, j
			* 50, i * 50);
	if (vars->map[i][j] == '0')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->map_s.imgs.f_img, j
			* 50, i * 50);
	if (vars->map[i][j] == 'P')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->map_s.imgs.p_img, j
			* 50, i * 50);
	if (vars->map[i][j] == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->map_s.imgs.e_img, j
			* 50, i * 50);
	if (vars->map[i][j] == 'N')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->map_s.imgs.n_img, j
			* 50, i * 50);
}
