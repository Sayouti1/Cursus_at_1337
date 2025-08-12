/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 09:33:40 by hbarda            #+#    #+#             */
/*   Updated: 2025/01/04 19:11:03 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_memset(data, 0, sizeof(t_data));
	if (!parse_map(data, ac, av))
		return (free(data), 1);
	if (init_cub(data))
		return (ft_close(data), free_all(data), free(data), 99);
	draw_map(data);
	mlx_hook(data->win, DestroyNotify, 0, ft_close, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, ft_key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, ft_key_release, data);
	mlx_loop_hook(data->ptr, update_map, data);
	mlx_loop(data->ptr);
	free_all(data);
	free(data);
	return (0);
}
