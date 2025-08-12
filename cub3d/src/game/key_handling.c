/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:14:52 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 19:18:29 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	valid_key(int key, t_data *data)
{
	int	ret;

	ret = 0;
	if (119 == key && ++ret)
		data->player.move_forward = 1;
	if (100 == key && ++ret)
		data->player.move_right = 1;
	if (115 == key && ++ret)
		data->player.move_forward = -1;
	if (97 == key && ++ret)
		data->player.move_right = -1;
	if (65363 == key && ++ret)
		data->player.turn_right = 1;
	if (65361 == key && ++ret)
		data->player.turn_right = -1;
	return (ret);
}

int	ft_key_press(int key, t_data *data)
{
	if (65307 == key)
		ft_close(data);
	else if (valid_key(key, data))
	{
		update_player(data);
		data->map.redraw = 1;
	}
	return (0);
}

int	ft_key_release(int key, t_data *data)
{
	if (119 == key || 115 == key)
		data->player.move_forward = 0;
	if (100 == key || 97 == key)
		data->player.move_right = 0;
	if (65363 == key || 65361 == key)
		data->player.turn_right = 0;
	return (0);
}
