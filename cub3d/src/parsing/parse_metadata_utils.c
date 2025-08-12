/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-08 15:50:06 by hbarda            #+#    #+#             */
/*   Updated: 2025-01-08 15:50:06 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_start_of_map(char *line)
{
	int	j;

	j = 0;
	while (line[j] && ft_isspace(line[j]))
		j++;
	return (line[j] == '1' || line[j] == '0');
}

int	parse_metadata_line(t_data *data, char *line, int *current_line)
{
	char	**parts;

	while (ft_isspace(*line))
		line++;
	data->trimmed = ft_strtrim(line, "\n");
	if (!data->trimmed)
		return (0);
	parts = split_on_two(data->trimmed, " \t");
	if (!parts)
	{
		free(data->trimmed);
		return (0);
	}
	if (!validate_identifier(data, parts, current_line))
	{
		free(data->trimmed);
		free_array(parts);
		return (0);
	}
	free(data->trimmed);
	free_array(parts);
	return (1);
}

int	process_metadata_lines(t_data *data, char **map_lines, int map_height,
		int *current_line)
{
	int	start_map;

	start_map = 0;
	while (*current_line < map_height)
	{
		if (is_empty_line(map_lines[*current_line]))
		{
			(*current_line)++;
			continue ;
		}
		if (is_start_of_map(map_lines[*current_line]))
		{
			start_map = 1;
			break ;
		}
		if (!parse_metadata_line(data, map_lines[*current_line], current_line))
			return (0);
		(*current_line)++;
	}
	return (start_map);
}
