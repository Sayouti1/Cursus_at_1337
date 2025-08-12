/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:04:18 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/02/06 18:04:20 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill_collectible(t_vars *vars, char **copy_map, int x, int y)
{
	if (x <= 0 || x >= vars->map_s.width - 1 || y <= 0
		|| y >= vars->map_s.height - 1 || copy_map[y][x] == '1'
		|| copy_map[y][x] == 'X' || copy_map[y][x] == 'E')
		return ;
	if (copy_map[y][x] == 'C')
		vars->map_s.c--;
	copy_map[y][x] = 'X';
	flood_fill_collectible(vars, copy_map, x + 1, y);
	flood_fill_collectible(vars, copy_map, x - 1, y);
	flood_fill_collectible(vars, copy_map, x, y + 1);
	flood_fill_collectible(vars, copy_map, x, y - 1);
}

int	flood_fill_exit(t_vars vars, char **copy_map, int x, int y)
{
	if (x <= 0 || x >= vars.map_s.width - 1 || y <= 0 || y >= vars.map_s.height
		- 1 || copy_map[y][x] == '1' || copy_map[y][x] == 'G')
		return (0);
	if (copy_map[y][x] == 'E')
		return (1);
	copy_map[y][x] = 'G';
	return (flood_fill_exit(vars, copy_map, x + 1, y) + flood_fill_exit(vars,
			copy_map, x - 1, y) + flood_fill_exit(vars, copy_map, x, y + 1)
		+ flood_fill_exit(vars, copy_map, x, y - 1));
}

int	check_map(t_vars *vars)
{
	if (!is_rectangular(*vars))
		return (print_error("Map should be rectangular !!", 0), 0);
	if (!is_surrounded(*vars))
		return (print_error("Map should be surrounded by Wall !!", 0), 0);
	if (!is_valid_path_to_exit(vars))
		return (print_error("Collectibles/Exit cannot be reached !!", 0), 0);
	return (1);
}

int	check_textures(t_vars *vars)
{
	if (!vars->map_s.imgs.c_img)
		return (print_error("Check collectible xpm file !", 0), 0);
	if (!vars->map_s.imgs.p_front_img)
		return (print_error("Check player xpm file !", 0), 0);
	if (!vars->map_s.imgs.p_back_img)
		return (print_error("Check player xpm file !", 0), 0);
	if (!vars->map_s.imgs.w_img)
		return (print_error("Check wall xpm file !", 0), 0);
	if (!vars->map_s.imgs.f_img)
		return (print_error("Check floor xpm file !", 0), 0);
	if (!vars->map_s.imgs.e_open_img)
		return (print_error("Check door xpm file !", 0), 0);
	if (!vars->map_s.imgs.e_close_img)
		return (print_error("Check door xpm file !", 0), 0);
	return (1);
}
