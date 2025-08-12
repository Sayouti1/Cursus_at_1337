/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 22:21:02 by aes-sayo          #+#    #+#             */
/*   Updated: 2023/11/16 17:00:26 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(char const *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			wcount++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wcount);
}

static void	ft_startend(char const *s, char c, size_t *start, size_t *end)
{
	while (s[*start] && s[*start] == c)
		(*start)++;
	*end = *start;
	while (s[*end] && s[*end] != c)
		(*end)++;
}

static char	**ft_free(char **words, int i)
{
	while (i--)
		free(words[i]);
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	start;
	size_t	end;
	int		i;

	if (!s || !ft_wcount(s, c))
		return (NULL);
	words = (char **) malloc((ft_wcount(s, c) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	start = 0;
	end = 0;
	while (i < ft_wcount(s, c))
	{
		ft_startend(s, c, &start, &end);
		words[i] = ft_substr(s, start, end - start);
		if (!words[i])
			return (ft_free(words, i));
		start = end;
		i++;
	}
	words[i] = NULL;
	return (words);
}
