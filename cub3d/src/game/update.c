/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:15:35 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 19:15:37 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	update_map(t_data *data)
{
	if (data->map.redraw)
	{
		if (data->rays)
			draw_map(data);
		data->map.redraw = 0;
	}
	return (0);
}

int	update_player(t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_angle;

	if (data->player.move_forward != 0)
	{
		move_forward_backward(data, &new_x, &new_y);
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	if (data->player.move_right != 0)
	{
		move_right_left(data, &new_x, &new_y);
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	if (data->player.turn_right != 0)
	{
		new_angle = turn_right_left(data, data->player.turn_right == 1);
		data->player.angle = new_angle;
	}
	return (0);
}
