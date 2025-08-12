/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:13:23 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 19:13:31 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	inter_check(t_data *data, int idx, double *inter, int is_horizon)
{
	if (is_horizon)
	{
		if (!data->rays[idx].is_facing_up)
		{
			*inter += data->screen.obj_size;
			return (1);
		}
	}
	else
	{
		if (data->rays[idx].is_facing_right)
		{
			*inter += data->screen.obj_size;
			return (1);
		}
	}
	return (-1);
}

t_intersection	get_horizontal_intersection(t_data *data, int i)
{
	t_intersection	h_inter;
	t_step			step;
	int				pixel;

	step.y = data->screen.obj_size;
	step.x = step.y / tan(data->rays[i].ray_angle);
	if (data->rays[i].is_facing_up)
		step.y *= -1;
	if ((data->rays[i].is_facing_right && step.x < 0)
		|| (!data->rays[i].is_facing_right && step.x > 0))
		step.x *= -1;
	h_inter.y = floor(data->player.pos_y / data->screen.obj_size)
		* data->screen.obj_size;
	pixel = inter_check(data, i, &h_inter.y, 1);
	h_inter.x = data->player.pos_x + ((h_inter.y - data->player.pos_y)
			/ tan(data->rays[i].ray_angle));
	while (player_inside_map(data, h_inter.x, h_inter.y + pixel))
	{
		h_inter.x += step.x;
		h_inter.y += step.y;
	}
	h_inter.distance = get_distance_between(data->player.pos_x,
			data->player.pos_y, h_inter.x, h_inter.y);
	return (h_inter);
}

t_intersection	get_vertical_intersection(t_data *data, int i)
{
	t_intersection	v_inter;
	t_step			step;
	int				pixel;

	step.x = data->screen.obj_size;
	step.y = step.x * tan(data->rays[i].ray_angle);
	if (!data->rays[i].is_facing_right)
		step.x *= -1;
	if ((data->rays[i].is_facing_up && step.y > 0)
		|| (!data->rays[i].is_facing_up && step.y < 0))
		step.y *= -1;
	v_inter.x = floor(data->player.pos_x / data->screen.obj_size)
		* data->screen.obj_size;
	pixel = inter_check(data, i, &v_inter.x, 0);
	v_inter.y = data->player.pos_y + ((v_inter.x - data->player.pos_x)
			* tan(data->rays[i].ray_angle));
	while (player_inside_map(data, v_inter.x + pixel, v_inter.y))
	{
		v_inter.x += step.x;
		v_inter.y += step.y;
	}
	v_inter.distance = get_distance_between(data->player.pos_x,
			data->player.pos_y, v_inter.x, v_inter.y);
	return (v_inter);
}
