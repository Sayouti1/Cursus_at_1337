/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:38:36 by aez-zoui          #+#    #+#             */
/*   Updated: 2024/09/05 22:38:39 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../include/include.h"

static int	check_value(char *str)
{
	int		i;
	char	*file;

	i = 0;
	file = ft_strtrim(str, " \t\n\v");
	if (file == NULL || *file == '\0')
		return (free(file), 1);
	while (file[i])
	{
		if (is_trim(file[i]))
			return (free(file), 1);
		i++;
	}
	return (free(file), 0);
}

int	ft_ambiguous_err(t_token *tokens)
{
	t_token	*token;
	char	*value;

	token = tokens;
	while (token)
	{
		if ((token->type == 3 || token->type == 2 || token->type == 4)
			&& token->next->type == 0 && ft_strchr(token->next->value, '$'))
		{
			value = substitute_var1(token->next->value);
			if (check_value(value))
				return (free(value), 1);
			free(value);
		}
		token = token->next;
	}
	return (0);
}

int	is_split(char *data)
{
	int	is_close_double;
	int	is_close_single;
	int	i;

	i = 0;
	is_close_double = 0;
	is_close_single = 0;
	while (data[i])
	{
		if (data[i] == '\'')
			is_close_single = !is_close_single;
		else if (data[i] == '"')
			is_close_double = !is_close_double;
		else if (data[i] == '$' && !is_close_double && !is_close_single)
			return (1);
		i++;
	}
	return (0);
}
