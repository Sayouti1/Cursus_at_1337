/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:14:04 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 19:14:07 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	get_distance_between(double x1, double y1, double x2, double y2)
{
	double	distance;

	distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	return (distance);
}

t_img	*get_img(t_data *data, int i)
{
	t_img	*img;

	if (data->rays[i].hit_vertical)
	{
		if (data->rays[i].is_facing_right)
			img = &data->textures.west;
		else
			img = &data->textures.east;
	}
	else
	{
		if (data->rays[i].is_facing_up)
			img = &data->textures.south;
		else
			img = &data->textures.north;
	}
	return (img);
}
