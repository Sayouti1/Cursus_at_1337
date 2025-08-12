/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:38:04 by hbarda            #+#    #+#             */
/*   Updated: 2025/01/03 18:13:12 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_texture_pos(char *texture_dir)
{
	if (!ft_strcmp("NO", texture_dir))
		return (NO);
	else if (!ft_strcmp("SO", texture_dir))
		return (SO);
	else if (!ft_strcmp("WE", texture_dir))
		return (WE);
	else if (!ft_strcmp("EA", texture_dir))
		return (EA);
	return (-1);
}

int	validate_texture_path(t_data *data, char **parts, char *path)
{
	if (!check_extension(path, ".xpm"))
	{
		free(path);
		free_parse_allocated(data, parts, "Error\nbad extension\n");
		return (0);
	}
	return (1);
}

int	store_texture_path(t_data *data, char **parts, char *path, int texture_pos)
{
	data->textures_path[texture_pos] = ft_strdup(path);
	if (!data->textures_path[texture_pos])
	{
		free(path);
		free_parse_allocated(data, parts, "Error\nMemory allocation failed\n");
		return (0);
	}
	return (1);
}

void	validate_texture_initial(t_data *data, char **parts,
		int *textures_found, int *texture_pos)
{
	if (!parts || !data || !textures_found)
		return ;
	*texture_pos = get_texture_pos(parts[0]);
	if (*texture_pos == -1)
	{
		free_parse_allocated(data, parts, "Error\nbad textures\n");
		return ;
	}
	if (data->textures_path[*texture_pos] != NULL)
	{
		free_parse_allocated(data, parts,
			"Error\nDuplicate texture definition\n");
		return ;
	}
}

void	validate_texture(t_data *data, char **parts, int *textures_found)
{
	int		texture_pos;
	char	*trimmed_path;

	validate_texture_initial(data, parts, textures_found, &texture_pos);
	trimmed_path = ft_strtrim(parts[1], " \t\r\v\f");
	if (!trimmed_path)
	{
		free_parse_allocated(data, parts, "Error\nMemory allocation failed\n");
		return ;
	}
	if (!validate_texture_path(data, parts, trimmed_path))
	{
		free(trimmed_path);
		return ;
	}
	if (!store_texture_path(data, parts, trimmed_path, texture_pos))
	{
		free(trimmed_path);
		return ;
	}
	free(trimmed_path);
	(*textures_found)++;
}
