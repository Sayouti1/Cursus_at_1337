/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:13:51 by aes-sayo          #+#    #+#             */
/*   Updated: 2025/01/09 09:43:30 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	draw_column(t_data *data, int x)
{
	int	y;

	y = -1;
	while (++y <= data->rays[x].top_y)
		put_color_to_pixel(data, x, y, data->textures.ceil_color);
	while (y <= data->rays[x].bottom_y)
		put_pixel_to_pixel(data, get_img(data, x), x, y++);
	while (y < data->screen.height)
		put_color_to_pixel(data, x, y++, data->textures.floor_color);
	return (0);
}

int	draw_ray(t_data *data, int x)
{
	double	wall_h;

	data->rays[x].distance *= cos(normalize_angle(data->rays[x].ray_angle
				- data->player.angle)) + 0.1;
	data->rays[x].wall_h = ((1 / data->rays[x].distance) * data->screen.height
			* 13.0);
	wall_h = fmin(data->rays[x].wall_h, data->screen.height);
	data->rays[x].bottom_y = floor((data->screen.height / 2) + (wall_h / 2));
	data->rays[x].r_bottom_y = floor((data->screen.height / 2)
			+ (data->rays[x].wall_h / 2));
	data->rays[x].top_y = floor((data->screen.height / 2) - (wall_h / 2));
	data->rays[x].r_top_y = floor((data->screen.height / 2)
			- (data->rays[x].wall_h / 2));
	if (data->rays[x].bottom_y > data->screen.height)
		data->rays[x].bottom_y = data->screen.height;
	if (data->rays[x].top_y < 0)
		data->rays[x].top_y = 0;
	draw_column(data, x);
	return (0);
}

int	draw_map(t_data *data)
{
	render_rays(data);
	mlx_put_image_to_window(data->ptr, data->win, data->img.img, 0, 0);
	return (0);
}
