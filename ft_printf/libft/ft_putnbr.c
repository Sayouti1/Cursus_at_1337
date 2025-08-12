/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:37:19 by aes-sayo          #+#    #+#             */
/*   Updated: 2023/12/08 03:39:39 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_putchar('-');
		return (1 + ft_putnbr(-n));
	}
	else if (n < 10)
	{
		return (ft_putchar(n + '0'));
	}
	else
	{
		count = ft_putnbr(n / 10);
		return (count + ft_putchar((n % 10) + '0'));
	}
}
