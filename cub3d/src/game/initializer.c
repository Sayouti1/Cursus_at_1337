/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:14:46 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/29 17:24:13 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	init_player(t_data *data)
{
	data->player.move_forward = 0;
	data->player.move_right = 0;
	data->player.turn_right = 0;
	data->player.fov = 60 * (PI / 180);
	data->player.move_speed = 0.9;
	data->player.turn_speed = 2.5;
	data->player.pos_x *= data->screen.obj_size;
	data->player.pos_y *= data->screen.obj_size;
	return (0);
}

static int	init_textures_2(t_data *data)
{
	data->textures.east.img = mlx_xpm_file_to_image(data->ptr,
			data->textures_path[EA], &data->textures.east.w,
			&data->textures.east.h);
	if (!data->textures.east.img)
		return (1);
	data->textures.east.addr = mlx_get_data_addr(data->textures.east.img,
			&data->textures.east.bpp, &data->textures.east.size_line,
			&data->textures.east.endian);
	data->textures.west.img = mlx_xpm_file_to_image(data->ptr,
			data->textures_path[WE], &data->textures.west.w,
			&data->textures.west.h);
	if (!data->textures.west.img)
		return (1);
	data->textures.west.addr = mlx_get_data_addr(data->textures.west.img,
			&data->textures.west.bpp, &data->textures.west.size_line,
			&data->textures.west.endian);
	return (0);
}

static int	init_textures(t_data *data)
{
	int	ret;

	data->textures.north.img = mlx_xpm_file_to_image(data->ptr,
			data->textures_path[NO], &data->textures.north.w,
			&data->textures.north.h);
	if (!data->textures.north.img)
		return (1);
	data->textures.north.addr = mlx_get_data_addr(data->textures.north.img,
			&data->textures.north.bpp, &data->textures.north.size_line,
			&data->textures.north.endian);
	data->textures.south.img = mlx_xpm_file_to_image(data->ptr,
			data->textures_path[SO], &data->textures.south.w,
			&data->textures.south.h);
	if (!data->textures.south.img)
		return (1);
	data->textures.south.addr = mlx_get_data_addr(data->textures.south.img,
			&data->textures.south.bpp, &data->textures.south.size_line,
			&data->textures.south.endian);
	ret = init_textures_2(data);
	return (ret);
}

static int	init_img(t_data *data)
{
	data->img.img = mlx_new_image(data->ptr, data->screen.width,
			data->screen.height);
	if (!data->img.img)
		return (1);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.size_line, &data->img.endian);
	if (!data->img.addr)
		return (1);
	return (0);
}

int	init_cub(t_data *data)
{
	data->screen.height = 1000;
	data->screen.width = 1900;
	data->screen.obj_size = 8;
	data->ptr = mlx_init();
	if (!data->ptr)
		return (printf("Error\n Cannot initialize mlx"), 1);
	data->win = mlx_new_window(data->ptr, data->screen.width,
			data->screen.height, "LCub3D");
	if (!data->win)
		return (printf("Error\n Cannot create window"), 1);
	if (init_img(data))
		return (printf("Error\n Cannot create image"), 1);
	if (init_player(data))
		return (1);
	if (init_textures(data))
		return (printf("Error\n Cannot initialize Textures"), 1);
	data->rays = malloc(sizeof(t_ray) * data->screen.width);
	if (!data->rays)
		return (printf("Error\n Cannot allocate for rays"), 1);
	return (0);
}
