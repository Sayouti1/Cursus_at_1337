/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:13:57 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 19:13:59 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_close(t_data *data)
{
	mlx_loop_end(data->ptr);
	free_textures(data);
	if (data->img.img)
	{
		mlx_destroy_image(data->ptr, data->img.img);
		data->img.img = NULL;
	}
	if (data->rays)
		free(data->rays);
	data->rays = NULL;
	return (0);
}

int	free_textures(t_data *data)
{
	if (data->textures.east.img)
	{
		mlx_destroy_image(data->ptr, data->textures.east.img);
		data->textures.east.img = NULL;
	}
	if (data->textures.west.img)
	{
		mlx_destroy_image(data->ptr, data->textures.west.img);
		data->textures.west.img = NULL;
	}
	if (data->textures.north.img)
	{
		mlx_destroy_image(data->ptr, data->textures.north.img);
		data->textures.north.img = NULL;
	}
	if (data->textures.south.img)
	{
		mlx_destroy_image(data->ptr, data->textures.south.img);
		data->textures.south.img = NULL;
	}
	return (0);
}
