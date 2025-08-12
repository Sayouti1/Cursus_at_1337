/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:29:04 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/06/28 09:30:17 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/include.h"

int	exit_overflow(char *arg)
{
	int		i;
	int		n;
	int		sign;
	long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(arg[i]))
		++i;
	if (ft_char_in(arg[i], "-+"))
		if (arg[i++] == '-')
			sign = -1;
	while (arg[i] && ft_isdigit(arg[i]))
	{
		n = arg[i++] - '0';
		if (sign == 1 && (result > (LONG_MAX - n) / 10))
			return (ft_perror("exit: ", arg, ": numeric argument required\n"),
				1);
		else if (sign == -1 && ((result * -1) < (LONG_MIN + n) / 10))
			return (ft_perror("exit:", arg, ": numeric argument required\n"),
				1);
		result = result * 10 + n;
	}
	return (0);
}

int	ft_exit(char **arg, int piped)
{
	int	exit_status;

	if (piped == 0)
		printf("exit\n");
	if (NULL == arg)
		exit_status = g_vars.exit_status;
	else if (str_isdigit(arg[0]) == 2)
		exit_status = 2;
	else if (split_len(arg) > 1)
		return (ft_putstr_fd("exit: too many arguments\n", 2),
			g_vars.exit_status = 1,
			1);
	else if (exit_overflow(arg[0]))
		exit_status = 2;
	else
		exit_status = ft_atoi(arg[0]);
	g_vars.exit_status = exit_status;
	close(g_vars.std_in);
	close(g_vars.std_out);
	free_env();
	free_cmds(g_vars.cmd);
	free_token(g_vars.token);
	close_file_ds();
	free_garbage();
	exit(exit_status);
}
