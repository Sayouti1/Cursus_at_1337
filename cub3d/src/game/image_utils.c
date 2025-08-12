/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:14:11 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 19:14:22 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	put_color_to_pixel(t_data *data, int x, int y, int col)
{
	unsigned int	*pixel;

	if (!pixel_in_screen(data, x, y))
		return (1);
	pixel = (unsigned int *)(data->img.addr + (y * data->img.size_line + x
				* 4));
	*pixel = col;
	return (0);
}

int	put_pixel_to_pixel(t_data *data, t_img *img, int x, int y)
{
	unsigned int	*dest_pixel;
	unsigned int	*src_pixel;
	int				offset_x;
	int				offset_y;

	if (!pixel_in_screen(data, x, y))
		return (1);
	if (data->rays[x].hit_vertical)
		offset_x = (int)((data->rays[x].hit_y / data->screen.obj_size) * img->w)
			% img->w;
	else
		offset_x = (int)((data->rays[x].hit_x / data->screen.obj_size) * img->w)
			% img->w;
	offset_y = ((y - data->rays[x].r_top_y) * img->h) / data->rays[x].wall_h;
	offset_y = offset_y % img->h;
	dest_pixel = (unsigned int *)(data->img.addr + (y * data->img.size_line + x
				* 4));
	src_pixel = (unsigned int *)(img->addr + (offset_y * img->size_line
				+ offset_x * 4));
	*dest_pixel = *src_pixel;
	return (0);
}
