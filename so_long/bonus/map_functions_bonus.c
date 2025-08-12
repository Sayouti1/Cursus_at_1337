/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:03:48 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/02/06 18:03:51 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_lines(char *old_line, char *buff)
{
	int		i;
	int		j;
	char	*new_line;

	j = ft_strlen_gnl(buff) + ft_strlen_gnl(old_line);
	new_line = (char *)malloc(sizeof(char) * (j + 1));
	if (!new_line)
	{
		free(old_line);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (old_line && old_line[i])
		new_line[j++] = old_line[i++];
	i = 0;
	while (buff[i])
		new_line[j++] = buff[i++];
	new_line[j] = '\0';
	if (old_line)
		free(old_line);
	return (new_line);
}

char	*read_file(int fd)
{
	char	*all_lines;
	char	*buff;
	int		byte_read;

	buff = (char *)malloc(sizeof(char) * 21);
	if (!buff)
		return (NULL);
	byte_read = 1;
	all_lines = NULL;
	while (byte_read > 0)
	{
		byte_read = read(fd, buff, 20);
		if (byte_read < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[byte_read] = '\0';
		all_lines = ft_strjoin_lines(all_lines, buff);
	}
	free(buff);
	return (all_lines);
}

char	**get_map(char *path)
{
	char	*all_lines;
	int		fd;
	char	**split_lines;

	all_lines = 0;
	if (!is_valid_ext(path))
		print_error("The file should end with .ber extension !", 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error("Cannot open the file !", 1);
	all_lines = read_file(fd);
	close(fd);
	if (!valid_map(all_lines))
	{
		free(all_lines);
		print_error("Map not Valid !", 1);
	}
	split_lines = ft_split(all_lines, '\n');
	free(all_lines);
	return (split_lines);
}

int	init_map(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map && vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'C')
				vars->map_s.c++;
			else if (vars->map[i][j] == 'E')
				vars->map_s.e++;
			else if (vars->map[i][j] == 'P')
				vars->map_s.p++;
			else if (vars->map[i][j] != '1' && vars->map[i][j] != '0'
					&& vars->map[i][j] != 'N')
				return (0);
			++j;
		}
		++i;
	}
	vars->map_s.width = j;
	vars->map_s.height = i;
	return (vars->map_s.c != 0 && vars->map_s.e == 1 && vars->map_s.p == 1);
}
