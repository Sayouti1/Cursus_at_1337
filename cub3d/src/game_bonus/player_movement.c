/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:15:09 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/29 14:55:16 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	player_wall_sliding(t_data *data, double *new_x, double *new_y)
{
	if (player_inside_map(data, data->player.pos_x, *new_y))
		*new_x = data->player.pos_x;
	else if (player_inside_map(data, *new_x, data->player.pos_y))
		*new_y = data->player.pos_y;
	else
	{
		*new_x = data->player.pos_x;
		*new_y = data->player.pos_y;
	}
	return (0);
}

int	move_forward_backward(t_data *data, double *new_x, double *new_y)
{
	if (data->player.move_forward == 1)
	{
		*new_x = data->player.pos_x + cos(data->player.angle)
			* data->player.move_speed;
		*new_y = data->player.pos_y + sin(data->player.angle)
			* data->player.move_speed;
	}
	else if (data->player.move_forward == -1)
	{
		*new_x = data->player.pos_x - cos(data->player.angle)
			* data->player.move_speed;
		*new_y = data->player.pos_y - sin(data->player.angle)
			* data->player.move_speed;
	}
	if (!player_inside_map(data, *new_x, *new_y))
		player_wall_sliding(data, new_x, new_y);
	return (0);
}

int	move_right_left(t_data *data, double *new_x, double *new_y)
{
	if (data->player.move_right == 1)
	{
		*new_x = data->player.pos_x + cos(data->player.angle + (PI / 2))
			* data->player.move_speed;
		*new_y = data->player.pos_y + sin(data->player.angle + (PI / 2))
			* data->player.move_speed;
	}
	else if (data->player.move_right == -1)
	{
		*new_x = data->player.pos_x + cos(data->player.angle - (PI / 2))
			* data->player.move_speed;
		*new_y = data->player.pos_y + sin(data->player.angle - (PI / 2))
			* data->player.move_speed;
	}
	if (!player_inside_map(data, *new_x, *new_y))
		player_wall_sliding(data, new_x, new_y);
	return (0);
}

double	turn_right_left(t_data *data, int turn_right)
{
	double	new_angle;

	new_angle = data->player.angle;
	if (turn_right)
		new_angle += (data->player.turn_speed * (PI / 180));
	else
		new_angle -= (data->player.turn_speed * (PI / 180));
	new_angle = normalize_angle(new_angle);
	return (new_angle);
}
