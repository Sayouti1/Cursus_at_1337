/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:53:14 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

char	*ft_strjoin_prefixed(char *s1, char c, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (NULL == s1 || NULL == s2)
		return (NULL);
	i = (int)ft_strlen(s1) + (int)ft_strlen(s2) + 2;
	join = (char *)malloc(sizeof(char) * i--);
	if (NULL == join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		join[j++] = s1[i++];
	join[j++] = c;
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}

char	*char_concat(char *line, char c)
{
	char	*concat;
	int		i;
	int		j;

	i = ft_strlen(line);
	concat = (char *)malloc(sizeof(char) * (i + 2));
	if (NULL == concat)
		return (NULL);
	concat[i] = c;
	j = 0;
	i = 0;
	while (line && line[i])
		concat[j++] = line[i++];
	concat[j++] = c;
	concat[j] = '\0';
	free(line);
	return (concat);
}

char	*string_concat(char *line, char *str)
{
	int		i;
	int		j;
	char	*concat;

	i = ft_strlen(str) + ft_strlen(line);
	concat = (char *)malloc(sizeof(char) * (i + 1));
	if (NULL == concat)
		return (NULL);
	i = 0;
	j = 0;
	while (line && line[i])
		concat[j++] = line[i++];
	i = 0;
	while (str && str[i])
		concat[j++] = str[i++];
	concat[j] = '\0';
	free(line);
	free(str);
	return (concat);
}

int	ft_perror(char *s1, char *s2, char *s3)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (s3)
		ft_putstr_fd(s3, 2);
	return (1);
}

int	closing_found(char *str, int start, char c)
{
	while (str[start])
	{
		if (str[++start] == c)
			return (1);
	}
	return (0);
}
