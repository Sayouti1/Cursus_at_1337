/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:26:33 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/02/06 18:26:35 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_vars(t_vars *vars)
{
	if (enemy_exists(vars->map) && vars->map_s.imgs.n_img)
		mlx_destroy_image(vars->mlx, vars->map_s.imgs.n_img);
	free_arr(vars->map);
	if (vars->map_s.imgs.w_img)
		mlx_destroy_image(vars->mlx, vars->map_s.imgs.w_img);
	if (vars->map_s.imgs.c_img)
		mlx_destroy_image(vars->mlx, vars->map_s.imgs.c_img);
	if (vars->map_s.imgs.e_close_img)
		mlx_destroy_image(vars->mlx, vars->map_s.imgs.e_close_img);
	if (vars->map_s.imgs.e_open_img)
		mlx_destroy_image(vars->mlx, vars->map_s.imgs.e_open_img);
	if (vars->map_s.imgs.f_img)
		mlx_destroy_image(vars->mlx, vars->map_s.imgs.f_img);
	if (vars->map_s.imgs.p_back_img)
		mlx_destroy_image(vars->mlx, vars->map_s.imgs.p_back_img);
	if (vars->map_s.imgs.p_front_img)
		mlx_destroy_image(vars->mlx, vars->map_s.imgs.p_front_img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

void	*free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
	return (0);
}

void	free_and_exit(t_vars *vars)
{
	free_vars(vars);
	exit(0);
}

int	close_x(t_vars *vars)
{
	free_and_exit(vars);
	return (0);
}

void	print_error(char *str, int end)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	if (end)
		exit(0);
}
