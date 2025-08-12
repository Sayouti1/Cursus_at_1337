/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:24:24 by hbarda            #+#    #+#             */
/*   Updated: 2025/01/04 12:45:54 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_int_array(int **int_array, int arr_len)
{
	int	i;

	i = -1;
	if (!int_array)
		return ;
	while (++i < arr_len)
		free(int_array[i]);
	free(int_array);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (i < NUM_TEXTURES)
	{
		if (data->textures_path[i])
			free(data->textures_path[i]);
		i++;
	}
	i = 0;
	free_array(data->lines);
	if (data->map.map_line_len)
		free(data->map.map_line_len);
	if (data->map.map)
		free_array(data->map.map);
	if (data->win)
		mlx_destroy_window(data->ptr, data->win);
	if (data->ptr)
	{
		mlx_destroy_display(data->ptr);
		free(data->ptr);
	}
}

void	ft_free_all(char *msg, t_data *data, int exit_status)
{
	int	i;

	i = -1;
	while (++i < data->textures_found)
	{
		if (data->texture[i] && data->texture[i]->img)
			mlx_destroy_image(data->ptr, data->texture[i]->img);
		free(data->texture[i]);
	}
	if (data)
		free_all(data);
	if (msg)
		write(2, msg, ft_strlen(msg));
	free (data);
	exit(exit_status);
}
