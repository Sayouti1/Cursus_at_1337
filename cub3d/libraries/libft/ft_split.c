/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 11:49:44 by hbarda            #+#    #+#             */
/*   Updated: 2024/12/28 11:49:59 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	ft_wcount(char *s, char c)
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

static void	ft_startend(char *s, char c, size_t *start, size_t *end)
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

char	**ft_split(char *s, char c)
{
	char	**words;
	size_t	start;
	size_t	end;
	int		i;

	if (!s || !ft_wcount(s, c))
		return (NULL);
	words = (char **)malloc((ft_wcount(s, c) + 1) * sizeof(char *));
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
