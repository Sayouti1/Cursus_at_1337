/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_test_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:42:57 by aez-zoui          #+#    #+#             */
/*   Updated: 2024/09/09 17:42:59 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

static void	print_args(char **args)
{
	int	j;

	j = 0;
	printf("\targs = {\n");
	while (args && args[j])
	{
		printf("\t\t[%d] = [%s],\n", j + 1, args[j]);
		j++;
	}
	printf("\t}\n");
}

static void	print_redirections(t_redirection *red)
{
	printf("\tredirection = {\n");
	while (red)
	{
		printf("\t\ttype = %d, file_name = [%s]\n", red->type, red->file_name);
		red = red->next;
	}
	printf("\t}\n");
}

static void	print_single_command(t_command *cmd, int i)
{
	printf("{\n\tcommand[%d] = [%s],\n", i, cmd->command);
	if (cmd->args)
		print_args(cmd->args);
	if (cmd->redirection)
		print_redirections(cmd->redirection);
	printf("}\n");
}

void	print_commands(t_command *command)
{
	int			i;
	t_command	*cmd;

	i = 0;
	cmd = command;
	while (cmd)
	{
		print_single_command(cmd, ++i);
		cmd = cmd->next;
	}
}

void	ft_print_token(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("value --> [%s] | type ---> %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}
