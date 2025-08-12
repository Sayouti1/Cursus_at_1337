/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:14:58 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/12/28 19:58:00 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*ft_strjoin_gnl(char *old_line, char *new_line)
{
	char	*join;
	int		i;
	int		j;

	i = ft_strlen(old_line) + ft_strlen(new_line);
	join = malloc(sizeof(char) * (i + 1));
	if (NULL == join)
		return (NULL);
	i = 0;
	j = 0;
	while (old_line && old_line[j])
		join[i++] = old_line[j++];
	j = 0;
	while (new_line && new_line[j])
		join[i++] = new_line[j++];
	join[i] = '\0';
	free(old_line);
	return (join);
}

int	pixel_inside_map(t_data *data, double x, double y)
{
	int	i;
	int	j;

	if (x < 0 || y < 0)
		return (0);
	j = (int)(x / data->screen.obj_size);
	i = (int)(y / data->screen.obj_size);
	if (i < 0 || i >= data->map.height)
		return (0);
	if (j < 0 || j >= ft_strlen(data->map.map[i]))
		return (0);
	return (1);
}

int	pixel_in_screen(t_data *data, double x, double y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x > data->screen.width || y > data->screen.height)
		return (0);
	return (1);
}

int	player_inside_map(t_data *data, double player_x, double player_y)
{
	int	i;
	int	j;

	if (!pixel_inside_map(data, player_x, player_y))
		return (0);
	i = (int)(player_y / data->screen.obj_size);
	j = (int)(player_x / data->screen.obj_size);
	return (data->map.map[i][j] != '1');
}
