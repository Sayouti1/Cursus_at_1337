/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:27:04 by hbarda            #+#    #+#             */
/*   Updated: 2025/01/04 16:17:04 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_first_last(t_data *data, char **map, int map_height)
{
	int	i;
	int	line;

	i = -1;
	line = 0;
	while (map[line][++i] && ft_strchr("1 ", map[line][i]))
		;
	if (map[line][i] != '\n')
	{
		printf("Error\ninvalid map border!\n");
		ft_free_all(NULL, data, 1);
	}
	i = -1;
	line = map_height - 1;
	while (map[line][++i] && ft_strchr("1 ", map[line][i]))
		;
	if (map[line][i] != '\n' && map[line][i] != '\0')
	{
		printf("Error\ninvalid map border!\n");
		ft_free_all(NULL, data, 1);
	}
	return (1);
}

double	set_player_angle(t_data *data, int i, int j)
{
	if (data->map.map[i][j] == 'N')
		data->player.angle = 1.5 * PI;
	else if (data->map.map[i][j] == 'S')
		data->player.angle = 0.5 * PI;
	else if (data->map.map[i][j] == 'W')
		data->player.angle = PI;
	else
		data->player.angle = 0;
	return (data->player.angle);
}

void	check_map_characters(t_data *data, int i, int j, int *is_player_found)
{
	if (!ft_strchr(SUPPORTED_CHARS, data->map.map[i][j]))
	{
		printf("Error\nunsupported metadata characters!\n");
		printf("%d: %s\n", i, data->map.map[i]);
		ft_free_all(NULL, data, 1);
	}
	if (ft_strchr(PLAYER_DIR, data->map.map[i][j]))
	{
		if (*is_player_found)
		{
			printf("Error\nmultiple players!\n");
			printf("%d: %s\n", i, data->map.map[i]);
			ft_free_all(NULL, data, 1);
		}
		data->player.pos_x = j + 0.5;
		data->player.pos_y = i + 0.5;
		data->player.angle = set_player_angle(data, i, j);
		*is_player_found = 1;
		data->map.map[i][j] = '0';
	}
}

int	validate_map(t_data *data)
{
	int	i;
	int	j;
	int	is_player_found;

	i = -1;
	is_player_found = 0;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < data->map.map_line_len[i])
			check_map_characters(data, i, j, &is_player_found);
	}
	if (!is_player_found)
	{
		printf("Error\nno player found!\n");
		ft_free_all(NULL, data, 1);
	}
	return (is_player_found);
}
