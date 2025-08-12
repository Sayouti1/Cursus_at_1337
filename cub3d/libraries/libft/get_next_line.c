/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:39:22 by hbarda            #+#    #+#             */
/*   Updated: 2024/12/28 10:56:25 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*get_read(char *str, int fd)
{
	char	*buffer;
	ssize_t	byte;

	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
	{
		free(str);
		return (NULL);
	}
	byte = 1;
	while (!ft_strchr(str, '\n'))
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte <= 0)
			break ;
		buffer[byte] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	if (byte < 0)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

static char	*get_line(char *str)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(line, str, i);
	line[i] = '\0';
	return (line);
}

static char	*left_lines(char *line, char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (str[i] == line[i] && str[i] && line[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_str = malloc(ft_strlen(str) - i + 1);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = get_read(str, fd);
	if (!str)
		return (NULL);
	line = get_line(str);
	if (!line)
		return (NULL);
	str = left_lines(line, str);
	return (line);
}
