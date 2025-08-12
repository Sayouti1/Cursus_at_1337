/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 05:44:52 by aes-sayo          #+#    #+#             */
/*   Updated: 2023/12/12 05:44:56 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_strjoin_gnl(char *old_line, char *buff)
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

char	*get_final_line(char *line)
{
	int		i;
	char	*final_line;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && (line[i] != '\n'))
		i++;
	final_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!final_line)
		return (NULL);
	i = 0;
	while (line[i] && (line[i] != '\n'))
	{
		final_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		final_line[i] = '\n';
		i++;
	}
	final_line[i] = '\0';
	return (final_line);
}

char	*fix_line(char *line)
{
	int		i;
	int		j;
	char	*next_line;

	i = 0;
	while (line[i] && (line[i] != '\n'))
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	next_line = (char *)malloc(sizeof(char) * (ft_strlen_gnl(line) - i + 1));
	if (!next_line)
		return (free(line), NULL);
	i++;
	j = 0;
	while (line[i])
		next_line[j++] = line[i++];
	next_line[j] = '\0';
	free(line);
	if (!next_line[0])
		return (free(next_line), NULL);
	return (next_line);
}
