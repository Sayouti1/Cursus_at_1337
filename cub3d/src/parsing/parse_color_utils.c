/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-08 16:32:39 by hbarda            #+#    #+#             */
/*   Updated: 2025-01-08 16:32:39 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_color_parsed(char **colors)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	free_array(colors);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	split_len(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		++i;
	return (i);
}

int	is_valide_color(char *col)
{
	char	**split;
	char	**tmp;
	int		i;
	int		j;

	split = ft_split(col, ',');
	if (!split)
		return (0);
	i = -1;
	while (split[++i])
	{
		j = ft_strlen(split[i]) - 1;
		while (j >= 0 && ft_isspace(split[i][j]))
			split[i][j--] = '\0';
		tmp = split_on_two(split[i], " \t");
		if (split_len(tmp) != 1)
			return (free_array(tmp), free_array(split), 0);
		free_array(tmp);
	}
	free_array(split);
	return (1);
}
