/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:36:58 by hbarda            #+#    #+#             */
/*   Updated: 2025/01/04 17:33:38 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	skip_leading_spaces(char *str, int i)
{
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

static void	handle_comma_spaces(char *str, int *i, char *cleaned, int *j)
{
	cleaned[(*j)++] = ',';
	(*i)++;
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
}

static void	process_char(char *str, int *i, char *cleaned, int *j)
{
	if (str[*i] == ',')
		handle_comma_spaces(str, i, cleaned, j);
	else if (!ft_isspace(str[*i]))
		cleaned[(*j)++] = str[(*i)++];
	else
		(*i)++;
}

char	*clean_color_str(char *str)
{
	int		i;
	int		j;
	char	*cleaned;

	i = 0;
	j = 0;
	cleaned = malloc(ft_strlen(str) + 1);
	if (!cleaned)
		return (NULL);
	i = skip_leading_spaces(str, i);
	while (str[i])
		process_char(str, &i, cleaned, &j);
	cleaned[j] = '\0';
	return (cleaned);
}

int	parse_color(char *str_color)
{
	int		color;
	char	**colors;
	char	*cleaned_str;

	color = -1;
	cleaned_str = clean_color_str(str_color);
	if (!cleaned_str)
		return (-1);
	if (!check_color_format(cleaned_str))
	{
		free(cleaned_str);
		printf("Error\ncolor format should be like this: 255,255,255\n");
		return (color);
	}
	colors = ft_split(cleaned_str, ',');
	free(cleaned_str);
	if (!colors || arr_len(colors) != 3)
	{
		if (colors)
			free_array(colors);
		return (-1);
	}
	color = get_color_parsed(colors);
	return (color);
}
