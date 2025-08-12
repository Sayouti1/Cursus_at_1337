/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-06 22:20:25 by hbarda            #+#    #+#             */
/*   Updated: 2025-01-06 22:20:25 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_isspace(char c)
{
	return ((c >= 7 && c <= 13) || c == 32);
}

static int	ft_char_in(char c, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (c == str[i])
			return (1);
		++i;
	}
	return (0);
}

static char	*get_word(char *str, char *del, int *start)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && !ft_char_in(str[i], del) && !ft_isspace(str[i]))
		i++;
	*start = i;
	word = (char *)malloc(sizeof(char) * i + 1);
	if (NULL == word)
		return (NULL);
	word[i--] = '\0';
	while (i >= 0)
	{
		word[i] = str[i];
		--i;
	}
	return (word);
}

static char	*get_rest_of_line(char *str, int start)
{
	char	*rest;
	int		i;

	while (str[start] && ft_isspace(str[start]))
		start++;
	i = (int)ft_strlen(str) - start;
	if (i == 0)
		return (NULL);
	rest = (char *)malloc(sizeof(char) * i + 1);
	if (NULL == rest)
		return (NULL);
	i = 0;
	while (str[start])
		rest[i++] = str[start++];
	rest[i] = '\0';
	return (rest);
}

char	**split_on_two(char *line, char *del)
{
	char	**split;
	int		i;

	split = (char **)malloc(sizeof(char *) * 3);
	if (NULL == split)
		return (NULL);
	split[0] = get_word(line, del, &i);
	split[1] = get_rest_of_line(line, i);
	split[2] = NULL;
	return (split);
}
