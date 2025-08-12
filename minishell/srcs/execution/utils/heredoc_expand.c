/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:16:16 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:04:06 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

char	*substitute_var(char *str)
{
	int		i;
	char	*concat;
	char	*key;

	concat = NULL;
	i = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] != '$')
			concat = char_concat(concat, str[i++]);
		if (str[i] == '$' && str[i + 1] == '?' && ++i && ++i)
			concat = string_concat(concat, ft_itoa(g_vars.exit_status));
		if (str[i] == '$')
		{
			if (str[i + 1] == '{')
				++i;
			key = get_dollar_key_v1(str, &i);
			while (str[i] && ft_char_in(str[i], " \t}"))
				++i;
			concat = string_concat(concat, ft_strdup(get_env_v1(key)));
			free(key);
		}
	}
	return (concat);
}

int	check_curly_braces(char *str)
{
	int	i;

	if (NULL == str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (!str[i + 1] || ft_isspace(str[i + 1])) && ++i)
			continue ;
		if (str[i] == '$' && str[i + 1] == '{')
		{
			i += 2;
			while (str[i] && !ft_char_in(str[i], " \n{}"))
				++i;
			if (str[i] != '}')
				return (1);
		}
		++i;
	}
	return (0);
}
