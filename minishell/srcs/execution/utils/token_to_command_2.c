/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_command_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:33:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/14 20:34:53 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

char	*trim_str(char *str)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (str && str[++i])
	{
		if (str[i] == '\'' && closing_found(str, i, '\''))
		{
			++i;
			while (str[i] && str[i] != '\'')
				tmp = char_concat(tmp, str[i++]);
		}
		else if (str[i] == '"' && closing_found(str, i, '"'))
		{
			++i;
			while (str[i] && str[i] != '"')
				tmp = char_concat(tmp, str[i++]);
		}
		else
			tmp = char_concat(tmp, str[i]);
	}
	free(str);
	return (tmp);
}

void	remove_quotes(t_command *cmd)
{
	int		i;
	char	*tmp;

	if (NULL == cmd)
		return ;
	tmp = trim_str(ft_strdup(cmd->command));
	if (cmd->command)
	{
		if (tmp == NULL)
			cmd->command = ft_strdup("");
		else
			cmd->command = tmp;
	}
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		tmp = trim_str(ft_strdup(cmd->args[i]));
		if (tmp == NULL)
			cmd->args[i] = ft_strdup("");
		else
			cmd->args[i] = tmp;
		++i;
	}
}

int	token_type_to_cmd_type(t_token_type type)
{
	if (TOKEN_REDIR_IN == type)
		return (INPUT);
	if (TOKEN_REDIR_OUT == type)
		return (OUTPUT);
	if (TOKEN_REDIR_APPEND == type)
		return (APPEND);
	if (TOKEN_REDIR_HEREDOC == type)
		return (HEREDOC);
	else
		return (printf("error token_type to cmd_type\n"), 99);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = malloc(new_size);
	if (NULL == new_ptr)
		return (free(ptr), NULL);
	ft_memset(new_ptr, 0, new_size);
	if (ptr)
	{
		if (old_size <= new_size)
			ft_memmove(new_ptr, ptr, old_size);
		else
			ft_memmove(new_ptr, ptr, new_size);
		free(ptr);
	}
	return (new_ptr);
}

int	has_null(t_redirection *red)
{
	t_redirection	*tmp;

	tmp = red;
	while (tmp)
	{
		if (tmp->type != HEREDOC && NULL == tmp->file_name)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
