/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:48:15 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/23 13:45:00 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_valid_pid(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == ' ')
		++i;
	if (str[i] == '-' && str[i + 1] != '0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		++i;
	j = ft_strlen(str) - 1;
	while (j >= 0 && str[j] == ' ')
		--j;
	if (i > j)
		return (0);
	while (str && str[i] && i <= j)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

void	ft_wait(int sig)
{
	(void)sig;
	ft_putstr_fd("\nMessage is being sent...!", 1);
}
