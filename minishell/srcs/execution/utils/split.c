/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:12:57 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	ft_char_in(char c, char *str)
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

static int	ft_wcount(char const *s, char *del)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i])
	{
		while (s[i] && ft_char_in(s[i], del))
			i++;
		if (s[i])
			wcount++;
		while (s[i] && !ft_char_in(s[i], del))
			i++;
	}
	return (wcount);
}

static void	ft_startend(char const *s, char *del, size_t *start, size_t *end)
{
	while (s[*start] && ft_char_in(s[*start], del))
		(*start)++;
	*end = *start;
	while (s[*end] && !ft_char_in(s[*end], del))
		(*end)++;
}

static char	**ft_free(char **words, int i)
{
	while (i--)
		free(words[i]);
	free(words);
	return (NULL);
}

char	**ft_split_del(char const *s, char *del)
{
	char	**words;
	size_t	start;
	size_t	end;
	int		i;

	if (NULL == s || !ft_wcount(s, del))
		return (NULL);
	words = (char **)malloc((ft_wcount(s, del) + 1) * sizeof(char *));
	if (NULL == words)
		return (NULL);
	i = 0;
	start = 0;
	end = 0;
	while (i < ft_wcount(s, del))
	{
		ft_startend(s, del, &start, &end);
		words[i] = ft_substr(s, start, end - start);
		if (NULL == words[i])
			return (ft_free(words, i));
		start = end;
		i++;
	}
	words[i] = NULL;
	return (words);
}
