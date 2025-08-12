/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:38:03 by aez-zoui          #+#    #+#             */
/*   Updated: 2024/09/17 00:30:49 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	helper_func(t_token *token)
{
	char	*expand;
	char	**words;
	int		i;

	i = 0;
	expand = substitute_var1(token->value);
	if (expand[0] == '"')
	{
		add_token_to_list(&token, new_token(token->type, expand));
		token = token->next;
		return ;
	}
	words = split_expand(expand);
	i = 0;
	while (words && words[i])
		add_token_to_list(&token, new_token(TOKEN_WORD, words[i++]));
	free_words(words);
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	if (!words)
		return ;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

char	*handle_dollar_sign(char *str, int *i, char *concat, int in_quotes)
{
	char	*key;

	if (str[*i + 1] == '?' && ++(*i) && ++(*i))
		return (string_concat(concat, ft_itoa(g_vars.exit_status)));
	else if (ft_isalnum(str[*i + 1]) && (in_quotes || (str[*i + 1] != '\''
				&& str[*i + 1] != ' ')))
	{
		if (str[*i + 1] == '{')
			++(*i);
		key = get_dollar_key_v1(str, i);
		concat = string_concat(concat, ft_strdup(get_env_v1(key)));
		free(key);
		return (concat);
	}
	return (char_concat(concat, str[(*i)++]));
}
