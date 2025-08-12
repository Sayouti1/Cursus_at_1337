/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_empty_spaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-08 15:37:03 by hbarda            #+#    #+#             */
/*   Updated: 2025-01-08 15:37:03 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	find_max_line_length(t_data *data)
{
	int	max_len;
	int	i;

	max_len = 0;
	i = 0;
	while (i < data->map.height)
	{
		if (data->map.map_line_len[i] > max_len)
			max_len = data->map.map_line_len[i];
		i++;
	}
	return (max_len);
}

static char	*create_filled_line(t_data *data, int i, int max_len)
{
	char	*new_line;
	int		j;

	new_line = malloc(max_len + 1);
	if (!new_line)
	{
		printf("Error\nMemory allocation failed\n");
		return (NULL);
	}
	j = 0;
	while (j < max_len)
	{
		if (j < data->map.map_line_len[i] && data->map.map[i][j] != ' ')
			new_line[j] = data->map.map[i][j];
		else
			new_line[j] = '1';
		j++;
	}
	new_line[max_len] = '\0';
	return (new_line);
}

void	fill_empty_spaces(t_data *data)
{
	int		i;
	int		max_len;
	char	*new_line;

	if (!data || !data->map.map)
		return ;
	max_len = find_max_line_length(data);
	i = 0;
	while (i < data->map.height)
	{
		new_line = create_filled_line(data, i, max_len);
		if (!new_line)
			return ;
		free(data->map.map[i]);
		data->map.map[i] = new_line;
		data->map.map_line_len[i] = max_len;
		i++;
	}
}
