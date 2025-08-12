/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-05 14:36:35 by hbarda            #+#    #+#             */
/*   Updated: 2025/01/15 11:14:36 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	prepare_map_data(t_data *data, char **lines, int *current_line,
		int height)
{
	int	i;

	while (*current_line < height && is_empty_line(lines[*current_line]))
		(*current_line)++;
	i = height;
	while (--i - *current_line > 0 && is_empty_line(lines[i]))
		;
	data->map.map_start = *current_line;
	data->map.height = i - *current_line + 1;
	i = *current_line;
	while (i <= data->map.map_start + data->map.height - 1)
	{
		if (is_empty_line(lines[i]))
			ft_free_all("Error\nmap contains empty lines!\n", data, 1);
		i++;
	}
}

static void	allocate_and_init_map(t_data *data, char **lines)
{
	int	j;
	int	len;

	data->map.map = copy_array(&lines[data->map.map_start], data->map.height);
	if (!data->map.map)
		ft_free_all("Error\nMemory allocation failed\n", data, 1);
	data->map.map_line_len = malloc(sizeof(int) * data->map.height);
	if (!data->map.map_line_len)
		ft_free_all("Error\nMemory allocation failed\n", data, 1);
	j = -1;
	while (++j < data->map.height)
	{
		len = ft_strlen(data->map.map[j]);
		if (len > 0 && data->map.map[j][len - 1] == '\n')
			len--;
		while (len > 0 && data->map.map[j][len - 1] == ' ')
			len--;
		data->map.map_line_len[j] = len;
	}
}

void	init_map(t_data *data, char **lines, int current_line, int height)
{
	prepare_map_data(data, lines, &current_line, height);
	allocate_and_init_map(data, lines);
}

int	validate_map_cont(t_data *data, char **lines, int height)
{
	int	current_line;

	current_line = 0;
	if (!parse_metadata(data, lines, height, &current_line))
	{
		ft_free_all(NULL, data, 1);
		return (0);
	}
	init_map(data, lines, current_line, height);
	free_array(lines);
	data->lines = NULL;
	if (!validate_map(data))
		return (0);
	if (!validate_map_borders(data, data->map.map, data->map.height))
		return (0);
	return (1);
}

int	parse_map(t_data *data, int ac, char **av)
{
	int	height;

	if (ac != 2)
	{
		printf("Error\nbad arguments!\nUsage: ./cub3d <map_path>\n");
		return (0);
	}
	ft_memset(&data->map, 0, sizeof(t_map));
	if (!check_extension(av[1], ".cub"))
		return (0);
	data->lines = read_map_lines(av[1], &height);
	if (!data->lines)
		return (0);
	if (!validate_map_cont(data, data->lines, height))
		return (0);
	return (1);
}
