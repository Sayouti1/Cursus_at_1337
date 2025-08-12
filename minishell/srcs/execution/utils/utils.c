/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:31:00 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:19:53 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (NULL == s1 || NULL == s2)
		return (-1337);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
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
