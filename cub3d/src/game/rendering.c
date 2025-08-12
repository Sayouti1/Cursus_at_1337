/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:15:16 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 22:25:25 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	render_rays(t_data *data)
{
	double	angle;
	int		i;

	angle = data->player.angle - (0.5 * data->player.fov);
	i = -1;
	while (data->rays && ++i < data->screen.width)
	{
		angle = normalize_angle(angle);
		if (angle < 0.001)
			angle += 0.000551;
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
