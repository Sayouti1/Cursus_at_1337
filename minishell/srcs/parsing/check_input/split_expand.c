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
#include "./../../../include/include.h"

int	is_trim(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v');
}

static int	ft_wcount(char const *s)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s && s[i])
	{
		while (s[i] && is_trim(s[i]))
			i++;
		if (s[i])
			wcount++;
		while (s[i] && !is_trim(s[i]))
			i++;
	}
	return (wcount);
}

static void	ft_startend(char const *s, size_t *start, size_t *end)
{
	while (s[*start] && is_trim(s[*start]))
		(*start)++;
	*end = *start;
	while (s[*end] && !is_trim(s[*end]))
		(*end)++;
}

static char	**ft_free(char **words, int i)
{
	while (i--)
		free(words[i]);
	free(words);
	return (NULL);
}

char	**split_expand(char const *s)
{
	char	**words;
	size_t	start;
	size_t	end;
	int		i;

	if (!s || !ft_wcount(s))
		return (NULL);
	words = (char **)malloc((ft_wcount(s) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	start = 0;
	end = 0;
	while (i < ft_wcount(s))
	{
		ft_startend(s, &start, &end);
		words[i] = ft_substr(s, start, end - start);
		if (!words[i])
			return (ft_free(words, i));
		start = end;
		i++;
	}
	words[i] = NULL;
	return (words);
}
