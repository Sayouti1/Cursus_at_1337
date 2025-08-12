/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:03:17 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/02/06 18:03:18 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	move_top(t_vars *vars, int x, int y)
{
	vars->moves++;
	if (vars->map[y - 1][x] == 'N')
	{
		ft_putendl_fd("OOPS! You got caught by the enemy!", 1);
		free_and_exit(vars);
	}
	if (vars->map[y - 1][x] == 'C')
		vars->map_s.c--;
	if (vars->map_s.c == 0)
		vars->map_s.imgs.e_img = vars->map_s.imgs.e_open_img;
	if (vars->map[y - 1][x] == 'E' && vars->map_s.c == 0)
		free_and_exit(vars);
	vars->map[y][x] = '0';
	vars->map[y - 1][x] = 'P';
	mlx_clear_window(vars->mlx, vars->win);
	start_map(vars);
	display_moves(vars);
}

void	move_right(t_vars *vars, int x, int y)
{
	vars->moves++;
	if (vars->map[y][x + 1] == 'N')
	{
		ft_putendl_fd("OOPS! You got caught by the enemy!", 1);
		free_and_exit(vars);
	}
	if (vars->map[y][x + 1] == 'C')
		vars->map_s.c--;
	if (vars->map_s.c == 0)
		vars->map_s.imgs.e_img = vars->map_s.imgs.e_open_img;
	if (vars->map[y][x + 1] == 'E' && vars->map_s.c == 0)
		free_and_exit(vars);
	vars->map[y][x] = '0';
	vars->map[y][x + 1] = 'P';
	mlx_clear_window(vars->mlx, vars->win);
	vars->map_s.imgs.p_img = vars->map_s.imgs.p_front_img;
	start_map(vars);
	display_moves(vars);
}

void	move_down(t_vars *vars, int x, int y)
{
	vars->moves++;
	if (vars->map[y + 1][x] == 'N')
	{
		ft_putendl_fd("OOPS! You got caught by the enemy!", 1);
		free_and_exit(vars);
	}
	if (vars->map[y + 1][x] == 'C')
		vars->map_s.c--;
	if (vars->map_s.c == 0)
		vars->map_s.imgs.e_img = vars->map_s.imgs.e_open_img;
	if (vars->map[y + 1][x] == 'E' && vars->map_s.c == 0)
		free_and_exit(vars);
	vars->map[y][x] = '0';
	vars->map[y + 1][x] = 'P';
	mlx_clear_window(vars->mlx, vars->win);
	start_map(vars);
	display_moves(vars);
}

void	move_left(t_vars *vars, int x, int y)
{
	vars->moves++;
	if (vars->map[y][x - 1] == 'N')
	{
		ft_putendl_fd("OOPS! You got caught by the enemy!", 1);
		free_and_exit(vars);
	}
	if (vars->map[y][x - 1] == 'C')
		vars->map_s.c--;
	if (vars->map_s.c == 0)
		vars->map_s.imgs.e_img = vars->map_s.imgs.e_open_img;
	if (vars->map[y][x - 1] == 'E' && vars->map_s.c == 0)
		free_and_exit(vars);
	vars->map[y][x] = '0';
	vars->map[y][x - 1] = 'P';
	mlx_clear_window(vars->mlx, vars->win);
	vars->map_s.imgs.p_img = vars->map_s.imgs.p_back_img;
	start_map(vars);
	display_moves(vars);
}

int	ft_input(int key, t_vars *vars)
{
	int	x;
	int	y;

	x = get_player_x(*vars);
	y = get_player_y(*vars);
	if (key == 65307)
		free_and_exit(vars);
	if (key == 119 && !(vars->map[y - 1][x] == '1' || (vars->map[y
				- 1][x] == 'E' && vars->map_s.c != 0)))
		move_top(vars, x, y);
	if (key == 100 && !(vars->map[y][x + 1] == '1' || (vars->map[y][x
			+ 1] == 'E' && vars->map_s.c != 0)))
		move_right(vars, x, y);
	if (key == 115 && !(vars->map[y + 1][x] == '1' || (vars->map[y
				+ 1][x] == 'E' && vars->map_s.c != 0)))
		move_down(vars, x, y);
	if (key == 97 && !(vars->map[y][x - 1] == '1' || (vars->map[y][x - 1] == 'E'
		&& vars->map_s.c != 0)))
		move_left(vars, x, y);
	return (0);
}
