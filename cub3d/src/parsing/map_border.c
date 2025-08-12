/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:38:33 by hbarda            #+#    #+#             */
/*   Updated: 2025/01/03 22:06:37 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_surroundings(t_data *data, int i, int j)
{
	if (i <= 0 || j >= data->map.map_line_len[i - 1] || data->map.map[i
			- 1][j] == ' ')
		return (0);
	if (i >= data->map.height - 1 || j >= data->map.map_line_len[i + 1]
		|| data->map.map[i + 1][j] == ' ')
		return (0);
	if (j <= 0 || data->map.map[i][j - 1] == ' ')
		return (0);
	if (j >= data->map.map_line_len[i] - 1 || data->map.map[i][j + 1] == ' ')
		return (0);
	return (1);
}

int	is_valid_cell_surroundings(t_data *data, int i, int j)
{
	if (data->map.map[i][j] == ' ')
		return (1);
	if (data->map.map[i][j] == '0' || ft_strchr(PLAYER_DIR,
			data->map.map[i][j]))
	{
		if (i == 0 || i == data->map.height - 1 || j == 0
			|| j == data->map.map_line_len[i] - 1)
			return (0);
		return (check_surroundings(data, i, j));
	}
	return (1);
}

int	check_map_cells(t_data *data, char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < data->map.map_line_len[i])
		{
			if (map[i][j] == '0' || ft_strchr(PLAYER_DIR, map[i][j]))
			{
				if (!is_valid_cell_surroundings(data, i, j))
				{
					printf("Error\nmap invalid!\n");
					ft_free_all(NULL, data, 1);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map_borders(t_data *data, char **map, int height)
{
	if (!check_first_last(data, map, data->map.height))
		return (0);
	if (!check_map_cells(data, map, height))
		return (0);
	fill_empty_spaces(data);
	return (1);
}
