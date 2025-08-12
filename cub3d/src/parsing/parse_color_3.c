/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-08 16:40:04 by hbarda            #+#    #+#             */
/*   Updated: 2025-01-08 16:40:04 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	validate_color_characters(char *trimmed_str, int color_len)
{
	int	i;
	int	sep_count;

	i = -1;
	sep_count = 0;
	while (++i < color_len)
	{
		if ((i == 0 || trimmed_str[i - 1] == ',') && trimmed_str[i] == '+')
			continue ;
		if (!ft_isdigit(trimmed_str[i]) && trimmed_str[i] != ',')
			return (0);
		if (trimmed_str[i] == ',')
			sep_count++;
	}
	if (sep_count != 2)
		return (0);
	return (1);
}

int	validate_color_values(char **colors)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (colors[i][0] == '\0' || (colors[i][0] == '+'
				&& colors[i][1] == '\0'))
			return (0);
	}
	return (1);
}

int	check_color_format(char *str_color)
{
	char	*trimmed_str;
	char	**colors;

	if (!str_color || !is_valide_color(str_color))
		return (0);
	trimmed_str = ft_strtrim(str_color, " \t\r\v\f");
	if (!trimmed_str)
		return (0);
	if (!validate_color_characters(trimmed_str, ft_strlen(trimmed_str)))
		return (free(trimmed_str), 0);
	colors = ft_split(trimmed_str, ',');
	free(trimmed_str);
	if (!colors || split_len(colors) != 3)
		return (free_array(colors), 0);
	if (!validate_color_values(colors))
		return (free_array(colors), 0);
	free_array(colors);
	return (1);
}
