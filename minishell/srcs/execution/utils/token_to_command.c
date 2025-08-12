/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:33:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/14 20:34:53 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

char	**add_to_list(char **old_list, char *to_add)
{
	int		i;
	char	**new_list;

	i = split_len(old_list);
	new_list = ft_realloc(old_list, i * sizeof(char *),
			(i + 2) * sizeof(char *));
	if (NULL == new_list)
		return (ft_putstr_fd("ERROR allocating new_list\n", 2), NULL);
	new_list[i] = to_add;
	new_list[++i] = NULL;
	return (new_list);
}

t_redirection	*add_redirection(t_redirection *red, t_token **token)
{
	int				red_type;
	t_redirection	*new_red;
	t_token			*tmp;

	red_type = token_type_to_cmd_type((*token)->type);
	tmp = *token;
	(*token) = (*token)->next;
	if (NULL == *token)
		new_red = new_redirection(red_type, NULL, -1, 0);
	else if ((*token)->type != TOKEN_WORD)
	{
		new_red = new_redirection(red_type, NULL, -1, !has_null(red));
		(*token) = tmp;
	}
	else
		new_red = new_redirection(red_type, (*token)->value, -1,
				!has_null(red));
	if (NULL == red)
		red = new_red;
	else
		get_last_red(red)->next = new_red;
	return (red);
}

void	copy_cmd_args(t_token **token, t_command **cmd)
{
	char	**args;

	args = NULL;
	free_split((*cmd)->args);
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		while ((*token) && (*token)->type == TOKEN_WORD)
		{
			if (NULL == (*cmd)->command)
				(*cmd)->command = (*token)->value;
			else
				args = add_to_list(args, (*token)->value);
			(*token) = (*token)->next;
		}
		while ((*token) && (*token)->type != TOKEN_PIPE
			&& (*token)->type != TOKEN_WORD)
		{
			(*cmd)->redirection = add_redirection((*cmd)->redirection, token);
			if (*token)
				(*token) = (*token)->next;
		}
	}
	(*cmd)->args = args;
}

int	token_to_command_convert(t_token *token, t_command **cmd)
{
	t_token		*tmp_token;
	t_command	*tmp_cmd;

	tmp_token = token;
	while (tmp_token)
	{
		tmp_cmd = new_command(NULL, NULL, NULL);
		if (tmp_token->type == TOKEN_WORD)
		{
			tmp_cmd->command = tmp_token->value;
			tmp_token = tmp_token->next;
		}
		copy_cmd_args(&tmp_token, &tmp_cmd);
		remove_quotes(tmp_cmd);
		add_to_cmds(cmd, tmp_cmd);
		if (tmp_token)
			tmp_token = tmp_token->next;
	}
	return (0);
}
