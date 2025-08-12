/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:15:25 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 20:04:13 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	set_ray_data(t_data *data, int i)
{
	t_intersection	horz_intersection;
	t_intersection	vert_intersection;

	horz_intersection = get_horizontal_intersection(data, i);
	vert_intersection = get_vertical_intersection(data, i);
	if (horz_intersection.distance < vert_intersection.distance)
	{
		data->rays[i].distance = horz_intersection.distance;
		data->rays[i].hit_x = horz_intersection.x;
		data->rays[i].hit_y = horz_intersection.y;
		data->rays[i].hit_vertical = 0;
	}
	else
	{
		data->rays[i].distance = vert_intersection.distance;
		data->rays[i].hit_x = vert_intersection.x;
		data->rays[i].hit_y = vert_intersection.y;
		data->rays[i].hit_vertical = 1;
	}
	return (0);
}
