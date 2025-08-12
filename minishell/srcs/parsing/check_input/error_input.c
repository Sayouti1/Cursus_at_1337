/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 21:44:20 by aez-zoui          #+#    #+#             */
/*   Updated: 2024/09/05 21:44:21 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../include/include.h"

int	is_syntaxe_cmd(char *line)
{
	if (is_closed_qoute(line))
	{
		ft_putstr_fd("Syntax error: unclosed quote\n", STDERR_FILENO);
		g_vars.exit_status = 2;
		return (1);
	}
	else if (is_error_logic(line))
	{
		ft_putstr_fd("Error: Logical operators '&&' and '||' \
		are not supported.\n", STDERR_FILENO);
		g_vars.exit_status = 2;
		return (1);
	}
	else if (is_error_misplaced(line))
	{
		ft_putstr_fd("minishell: syntax error near unexpected \
		token `|` or `&`\n", STDERR_FILENO);
		g_vars.exit_status = 2;
		return (1);
	}
	else if (is_invalid_redirection(line))
	{
		ft_putstr_fd("sytax error : in invalid redirection\n", STDERR_FILENO);
		g_vars.exit_status = 2;
		return (1);
	}
	return (0);
}

int	is_closed_qoute(char *line)
{
	char	is_closed;

	is_closed = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			if (is_closed == *line)
				is_closed = 0;
			else if (!is_closed)
				is_closed = *line;
		}
		line++;
	}
	return (is_closed != 0);
}

int	is_invalid_redirection(char *line)
{
	int	sq_count;
	int	dq_count;

	sq_count = 0;
	dq_count = 0;
	while (*line)
	{
		update_quote_counts(*line, &sq_count, &dq_count);
		if ((!(sq_count % 2) && !(dq_count % 2)) && (*line == '>'
				|| *line == '<'))
		{
			if (is_invalid_op(&line))
				return (1);
		}
		else
			line++;
	}
	return (0);
}

int	is_error_misplaced(char *line)
{
	int	sq_count;
	int	dq_count;
	int	is_some;

	sq_count = 0;
	dq_count = 0;
	is_some = 0;
	if (*line == '|' || *line == '&')
		return (1);
	while (*line)
	{
		update_quote_counts(*line, &sq_count, &dq_count);
		if (*line == '|' && !(sq_count % 2) && !(dq_count % 2))
		{
			if (is_some)
				return (1);
			is_some = 1;
		}
		else if (!ft_isspace(*line))
			is_some = 0;
		line++;
	}
	if (is_some)
		return (1);
	return (0);
}

int	is_error_logic(char *line)
{
	int	dq_count;
	int	sq_count;
	int	i;

	dq_count = 0;
	sq_count = 0;
	i = 0;
	while (line[i])
	{
		update_quote_counts(line[i], &sq_count, &dq_count);
		if (!(dq_count % 2) && !(sq_count % 2))
		{
			if ((line[i] == '|' && line[i + 1] == '|') || (line[i] == '&'
					&& line[i + 1] == '&'))
				return (1);
		}
		i++;
	}
	return (0);
}
