/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 09:39:24 by hbarda            #+#    #+#             */
/*   Updated: 2025/01/04 14:45:14 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_extension(const char *file_path, const char *extension)
{
	int	fd;
	int	extension_len;
	int	file_path_len;

	if (!file_path || !extension)
		return (0);
	file_path_len = ft_strlen(file_path);
	if ((file_path_len == 4 && ft_strncmp(file_path, ".cub", 4) == 0))
		return (printf("Error\nInvalid file!\n"), 0);
	if (file_path_len >= 5 && ft_strncmp(&file_path[file_path_len - 5], "/.cub",
			5) == 0)
		return (printf("Error\nInvalid file!\n"), 0);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nFile does not exist!\n"), 0);
	else
		close(fd);
	extension_len = ft_strlen(extension);
	if (!ft_strnstr(&file_path[ft_strlen(file_path) - extension_len], extension,
			extension_len))
		return (printf("Error\nbad file extension [example.cub]!\n"), 0);
	return (1);
}

int	is_empty_line(const char *line)
{
	int	i;

	i = -1;
	if (!line)
		return (1);
	while (line[++i] && ft_isspace(line[i]))
		;
	return (!line[i]);
}

int	is_empty_map(const char *map_path, int *height)
{
	int		fd;
	char	*line;
	int		is_empty;

	is_empty = 1;
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nfailled to open map file!\n"), 0);
	*height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
			is_empty = 0;
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	if (*height == 0 || is_empty)
		return (printf("Error\nmap file is empty!\n"), close(fd), 0);
	close(fd);
	return (1);
}

char	**read_lines(int fd, int *height)
{
	int		i;
	char	**lines;

	i = -1;
	lines = malloc(sizeof(char *) * (*height + 1));
	if (!lines)
	{
		printf("Error\nfailed to allocate memory for the map!\n");
		return (NULL);
	}
	while (++i < *height)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
		{
			while (--i >= 0)
				free(lines[i]);
			free(lines);
			printf("Error\nfailed to get next line!\n");
			return (NULL);
		}
	}
	lines[*height] = NULL;
	return (lines);
}

char	**read_map_lines(const char *map_path, int *height)
{
	int		fd;
	char	**lines;

	*height = 0;
	if (!is_empty_map(map_path, height))
		return (NULL);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nfailled to open map file!\n");
		return (NULL);
	}
	lines = read_lines(fd, height);
	close(fd);
	return (lines);
}
