/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:14:47 by aes-sayo          #+#    #+#             */
/*   Updated: 2023/12/06 18:14:59 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

void	ft_print_hex(unsigned int n, char x)
{
	if (n >= 16)
	{
		ft_print_hex(n / 16, x);
		ft_print_hex(n % 16, x);
	}
	else
	{
		if (n < 10)
			ft_putchar(n + '0');
		else
		{
			if (x == 'x')
				ft_putchar(n - 10 + 'a');
			if (x == 'X')
				ft_putchar(n - 10 + 'A');
		}
	}
}

int	ft_puthex(unsigned int n, char x)
{
	if (n == 0)
		return (ft_putchar('0'));
	ft_print_hex(n, x);
	return (ft_len(n));
}
