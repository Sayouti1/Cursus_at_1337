/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:31:00 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/08/04 13:19:53 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	ft_isspace(char c)
{
	return ((c >= 7 && c <= 13) || c == 32);
}

int	str_isdigit(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (NULL == str)
		return (0);
	while (ft_char_in(str[i], " \t"))
		++i;
	j = ft_strlen(str) - 1;
	while (j >= 0 && ft_char_in(str[j], " \t"))
		--j;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[i] && i <= j)
		if (!ft_isdigit(str[i++]))
			return (ft_perror("exit: ", str, ": numeric argument required\n"),
				2);
	return (1);
}

int	fix_command_path(t_command *cmd)
{
	char	*cwd;
	char	*tmp_cmd;
	int		ret;

	ret = 0;
	tmp_cmd = cmd->command;
	cwd = getcwd(NULL, 0);
	cmd->command = get_full_path(cmd->command, cwd);
	if (NULL == cmd->command && ++ret)
	{
		ft_putstr_fd("minishell ", 2);
		ft_putstr_fd(tmp_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_vars.exit_status = 127;
	}
	free(cwd);
	free(tmp_cmd);
	if (cmd->command)
		fix_command_arg(cmd);
	update_under_s(cmd);
	return (ret);
}

void	update_under_s(t_command *command)
{
	char		*tmp;
	int			i;
	t_command	*cmd;

	if (NULL == command)
		return ;
	cmd = command;
	i = 0;
	tmp = cmd->command;
	while (cmd->args && cmd->args[i])
	{
		tmp = cmd->args[i];
		++i;
	}
	if (ft_env_replace("_", tmp) == 0)
		add_to_env(ft_strdup("_"), ft_strdup(tmp), 1);
}
