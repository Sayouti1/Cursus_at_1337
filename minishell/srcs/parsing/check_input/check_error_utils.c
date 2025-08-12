/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:44:01 by aez-zoui          #+#    #+#             */
/*   Updated: 2024/09/05 21:44:09 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

void	update_quote_counts(char c, int *s_q_count, int *d_q_count)
{
	if (c == 34)
		(*d_q_count)++;
	else if (c == 39)
		(*s_q_count)++;
}

char	*skip_spaces(char *input)
{
	while (*input && (*input == ' ' || *input == '\t'))
	{
		input++;
	}
	return (input);
}

int	is_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	check_line(char **line)
{
	if (*line[0] == '\0' || _strcmp(*line, "\n", NULL) || is_space(*line))
	{
		free(*line);
		return (1);
	}
	return (0);
}

int	is_invalid_op(char **line)
{
	char	*op_st;

	op_st = *line;
	(*line)++;
	if (*op_st == **line)
		(*line)++;
	*line = skip_spaces(*line);
	if (**line == '\0' || **line == '>' || **line == '<' || **line == '|')
		return (1);
	return (0);
}
