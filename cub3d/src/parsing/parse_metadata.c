/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:41:49 by hbarda            #+#    #+#             */
/*   Updated: 2025/01/04 17:27:41 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_args_num(t_data *data, char **parts, int *current_line)
{
	if (!parts || arr_len(parts) != 2)
	{
		printf("Error\nbad texture or color arguments!\n");
		printf("%d: %s\n", *current_line, data->trimmed);
		free_parse_allocated(data, parts, NULL);
	}
}

int	validate_identifier(t_data *data, char **parts, int *current_line)
{
	if (!ft_strcmp("F", parts[0]) || !ft_strcmp("C", parts[0]))
	{
		if (data->colors_found >= NUM_COLORS)
		{
			printf("Error\nfound more than 2 colors!\n");
			return (0);
		}
		validate_color(data, parts, current_line, &data->colors_found);
	}
	else if (get_texture_pos(parts[0]) != -1)
	{
		if (data->textures_found >= NUM_TEXTURES)
		{
			printf("Error\nfound more than 4 textures!\n");
			return (0);
		}
		validate_texture(data, parts, &data->textures_found);
	}
	else
	{
		printf("Error\nInvalid identifier %s\n", parts[0]);
		return (0);
	}
	return (1);
}

int	parse_metadata(t_data *data, char **map_lines, int map_height,
		int *current_line)
{
	int	start_map;

	start_map = process_metadata_lines(data, map_lines, map_height,
			current_line);
	return (start_map && data->textures_found == NUM_TEXTURES
		&& data->colors_found == NUM_COLORS);
}
