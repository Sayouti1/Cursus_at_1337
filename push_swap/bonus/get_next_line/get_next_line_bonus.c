/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 05:44:28 by aes-sayo          #+#    #+#             */
/*   Updated: 2023/12/12 05:44:32 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*final_line;

	if (fd < 0)
		return (NULL);
	line = get_text(fd, line);
	if (line == NULL)
		return (NULL);
	final_line = get_final_line(line);
	line = fix_line(line);
	return (final_line);
}

int	check_new_line(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_text(int fd, char *line)
{
	char	*buff;
	int		bytes_read;

	buff = (char *)malloc(sizeof(char) * (5));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	bytes_read = 1;
	while (!check_new_line(buff) && bytes_read != 0)
	{
		bytes_read = read(fd, buff, 4);
		if (bytes_read == -1)
		{
			free(buff);
			free(line);
			line = NULL;
			return (NULL);
		}
		buff[bytes_read] = '\0';
		line = ft_strjoin_gnl(line, buff);
	}
	free(buff);
	return (line);
}
