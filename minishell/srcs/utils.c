/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:43:35 by aez-zoui          #+#    #+#             */
/*   Updated: 2024/09/17 00:30:28 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

int	handle_tokens(t_token **tokens, t_token **ntokens)
{
	if (ft_ambiguous_err(*tokens))
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
	if (error_heredoc(*tokens))
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
		free_token(*tokens);
		free_cmds(g_vars.cmd);
		free_garbage();
		free_env();
		close(g_vars.std_in);
		close(g_vars.std_out);
		exit (2);
	}
	*ntokens = expand_var(*tokens);
	free_token(*tokens);
	return (*ntokens == NULL);
}

void	process_line(char *line, t_command **command)
{
	t_token	*tokens;
	t_token	*ntokens;

	tokens = check_and_token(line);
	if (tokens && !handle_tokens(&tokens, &ntokens))
	{
		g_vars.token = ntokens;
		token_to_command_convert(ntokens, command);
		process_command(*command);
		free_cmds(*command);
		*command = NULL;
		free_token(ntokens);
		free_garbage();
		ntokens = NULL;
	}
}

t_token	*check_and_token(char *line)
{
	char	*line_trim;
	t_token	*tokens;

	tokens = NULL;
	line_trim = line;
	line_trim = ft_strtrim(line, " \t\n\v\r");
	free(line);
	if (!line_trim)
		return (NULL);
	if (is_syntaxe_cmd(line_trim))
	{
		free(line_trim);
		return (NULL);
	}
	tokens = token_line(line_trim);
	free(line_trim);
	return (tokens);
}
