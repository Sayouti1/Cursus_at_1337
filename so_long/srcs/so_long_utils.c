/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:59:23 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/02/03 15:59:26 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_vars(t_vars *vars)
{
	vars->win_x = 0;
	vars->win_y = 0;
	vars->map_s.c = 0;
	vars->map_s.e = 0;
	vars->map_s.p = 0;
	vars->map_s.height = 0;
	vars->map_s.width = 0;
	vars->moves = 0;
}

int	valid_map(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] == '\n')
		i++;
	if (i >= 1)
		return (0);
	while (str && str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			return (0);
		++i;
	}
	return (1);
}
