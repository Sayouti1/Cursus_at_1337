/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:04:07 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/02/06 18:04:09 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	display_moves(t_vars *vars)
{
	char	*string;
	char	*moves;

	moves = ft_itoa(vars->moves);
	string = ft_strjoin("Total moves is : ", moves);
	mlx_string_put(vars->mlx, vars->win, 10, 20, 0xFFFFFF, string);
	free(moves);
	free(string);
}

void	load_images(t_vars *vars)
{
	vars->map_s.imgs.c_img = mlx_xpm_file_to_image(vars->mlx,
			"./textures/c_50.xpm",
			&vars->map_s.imgs.width,
			&vars->map_s.imgs.height);
	vars->map_s.imgs.e_open_img = mlx_xpm_file_to_image(vars->mlx,
			"./textures/door_opened_50.xpm",
			&vars->map_s.imgs.width,
			&vars->map_s.imgs.height);
	if (enemy_exists(vars->map))
		vars->map_s.imgs.n_img = mlx_xpm_file_to_image(vars->mlx,
				"./textures/zombie1_50.xpm",
				&vars->map_s.imgs.width,
				&vars->map_s.imgs.height);
	load_images_compl(vars);
	if (!check_textures(vars))
		free_and_exit(vars);
	vars->map_s.imgs.p_img = vars->map_s.imgs.p_front_img;
	vars->map_s.imgs.e_img = vars->map_s.imgs.e_close_img;
}

void	load_images_compl(t_vars *vars)
{
	vars->map_s.imgs.f_img = mlx_xpm_file_to_image(vars->mlx,
			"./textures/floor_50px.xpm",
			&vars->map_s.imgs.width,
			&vars->map_s.imgs.height);
	vars->map_s.imgs.w_img = mlx_xpm_file_to_image(vars->mlx,
			"./textures/wall_w50V2.xpm",
			&vars->map_s.imgs.width,
			&vars->map_s.imgs.height);
	vars->map_s.imgs.p_front_img = mlx_xpm_file_to_image(vars->mlx,
			"./textures/soldier1_50new.xpm",
			&vars->map_s.imgs.width,
			&vars->map_s.imgs.height);
	vars->map_s.imgs.p_back_img = mlx_xpm_file_to_image(vars->mlx,
			"./textures/soldier_back_50new.xpm",
			&vars->map_s.imgs.width,
			&vars->map_s.imgs.height);
	vars->map_s.imgs.e_close_img = mlx_xpm_file_to_image(vars->mlx,
			"./textures/doorV2_w50.xpm",
			&vars->map_s.imgs.width,
			&vars->map_s.imgs.height);
}

void	start_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map_s.height)
	{
		j = 0;
		while (j < vars->map_s.width)
		{
			display_image_at(vars, i, j);
			++j;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		return (0);
	init_vars(&vars);
	vars.map = get_map(av[1]);
	if (!init_map(&vars))
	{
		free_arr(vars.map);
		print_error("Verify the map's elements !!", 1);
	}
	if (!check_map(&vars))
		return (free_arr(vars.map), 0);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (free_arr(vars.map), 0);
	vars.win = mlx_new_window(vars.mlx, vars.map_s.width * 50, vars.map_s.height
			* 50, "so_long");
	load_images(&vars);
	start_map(&vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, ft_input, &vars);
	mlx_hook(vars.win, DestroyNotify, 0, close_x, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
