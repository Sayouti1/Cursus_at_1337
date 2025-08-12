/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:04:30 by aes-sayo          #+#    #+#             */
/*   Updated: 2025/01/09 10:04:32 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	draw_square_at(t_data *data, double x, double y, int col)
{
	double	x1;
	double	y1;

	x = x * data->screen.obj_size;
	y = y * data->screen.obj_size;
	y1 = y - 1;
	while (++y1 < y + data->screen.obj_size)
	{
		x1 = x;
		while (x1 < x + data->screen.obj_size)
		{
			put_color_to_pixel(data, x1, y1, col);
			++x1;
		}
	}
	return (0);
}

int	draw_aim_cross(t_data *data)
{
	mlx_pixel_put(data->ptr, data->win, data->screen.width / 2,
		data->screen.height / 2, 0xFF0000);
	mlx_pixel_put(data->ptr, data->win, data->screen.width / 2,
		data->screen.height / 2 - 1, 0xFF0000);
	mlx_pixel_put(data->ptr, data->win, data->screen.width / 2,
		data->screen.height / 2 - 2, 0xFF0000);
	mlx_pixel_put(data->ptr, data->win, data->screen.width / 2,
		data->screen.height / 2 + 1, 0xFF0000);
	mlx_pixel_put(data->ptr, data->win, data->screen.width / 2,
		data->screen.height / 2 + 2, 0xFF0000);
	mlx_pixel_put(data->ptr, data->win, data->screen.width / 2 + 1,
		data->screen.height / 2, 0xFF0000);
	mlx_pixel_put(data->ptr, data->win, data->screen.width / 2 + 2,
		data->screen.height / 2, 0xFF0000);
	mlx_pixel_put(data->ptr, data->win, data->screen.width / 2 - 1,
		data->screen.height / 2, 0xFF0000);
	mlx_pixel_put(data->ptr, data->win, data->screen.width / 2 - 2,
		data->screen.height / 2, 0xFF0000);
	return (0);
}
