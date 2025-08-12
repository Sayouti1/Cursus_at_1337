/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:15:16 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 23:17:24 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	render_map(t_data *data, int s, int e)
{
	int	i;
	int	j;
	int	x;
	int	y;

	set_offset_x_y(data, &x, &y);
	i = -1 + y;
	while (data->map.map[++i] && i * data->screen.obj_size <= data->player.pos_y
		+ 80)
	{
		j = -1 + x;
		while (data->map.map[i][++j] && j
			* data->screen.obj_size <= data->player.pos_x + 150)
		{
			if (data->map.map[i][j] == '1')
				draw_square_at(data, s++, e, 0x078bf7);
			else
				draw_square_at(data, s++, e, 0xFFFFFF);
		}
		s = 0;
		e++;
	}
	return (0);
}

int	render_rays(t_data *data)
{
	double	angle;
	int		i;

	angle = data->player.angle - (0.5 * data->player.fov);
	i = -1;
	while (data->rays && ++i < data->screen.width)
	{
		angle = normalize_angle(angle);
		data->rays[i].ray_angle = angle;
		data->rays[i].is_facing_up = angle >= PI;
		data->rays[i].is_facing_right = angle < (0.5 * PI) || angle > (1.5
				* PI);
		set_ray_data(data, i);
		draw_ray(data, i);
		angle += data->player.fov / data->screen.width;
	}
	return (0);
}

int	render_player(t_data *data)
{
	int	x;
	int	y;

	set_offset_x_y(data, &x, &y);
	put_color_to_pixel(data, data->player.pos_x - x * data->screen.obj_size,
		data->player.pos_y - y * data->screen.obj_size, 0xFF0000);
	put_color_to_pixel(data, data->player.pos_x - x * data->screen.obj_size,
		(data->player.pos_y + 1) - y * data->screen.obj_size, 0xFF0000);
	put_color_to_pixel(data, (data->player.pos_x + 1) - x
		* data->screen.obj_size, data->player.pos_y - y * data->screen.obj_size,
		0xFF0000);
	put_color_to_pixel(data, data->player.pos_x - x * data->screen.obj_size,
		(data->player.pos_y - 1) - y * data->screen.obj_size, 0xFF0000);
	put_color_to_pixel(data, (data->player.pos_x - 1) - x
		* data->screen.obj_size, data->player.pos_y - y * data->screen.obj_size,
		0xFF0000);
	return (0);
}
