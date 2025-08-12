/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-08 16:36:12 by hbarda            #+#    #+#             */
/*   Updated: 2025-01-08 16:36:12 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_floor_color(t_data *data, char **parts)
{
	if (data->textures.floor_color != '\0')
	{
		free_parse_allocated(data, parts, "Error\nDuplicate color!\n");
		return (0);
	}
	return (1);
}

static int	get_ceiling_color(t_data *data, char **parts)
{
	if (data->textures.ceil_color != '\0')
	{
		free_parse_allocated(data, parts, "Error\nDuplicate color!\n");
		return (0);
	}
	return (1);
}

static int	*get_color_pointer(t_data *data, char **parts)
{
	if (!ft_strcmp("F", parts[0]))
	{
		if (!get_floor_color(data, parts))
			return (NULL);
		return (&data->textures.floor_color);
	}
	if (!ft_strcmp("C", parts[0]))
	{
		if (!get_ceiling_color(data, parts))
			return (NULL);
		return (&data->textures.ceil_color);
	}
	free_parse_allocated(data, parts, "Error\nbad textures!\n");
	return (NULL);
}

static void	process_color(t_data *data, char **parts, int *current_line,
		int *color_ptr)
{
	if (!parts || !parts[1])
	{
		printf("Error\nmissing color value!\n");
		printf("%d: %s\n", *current_line, data->trimmed);
		free_parse_allocated(data, parts, NULL);
		return ;
	}
	*color_ptr = parse_color(parts[1]);
	if (*color_ptr == -1)
	{
		printf("Error\nbad color!\n");
		printf("%d: %s\n", *current_line, data->trimmed);
		free_parse_allocated(data, parts, NULL);
	}
}

void	validate_color(t_data *data, char **parts, int *current_line,
		int *colors_found)
{
	int	*color_ptr;

	color_ptr = get_color_pointer(data, parts);
	if (color_ptr)
	{
		process_color(data, parts, current_line, color_ptr);
		(*colors_found)++;
	}
}
