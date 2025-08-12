/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:24:10 by aes-sayo          #+#    #+#             */
/*   Updated: 2023/11/19 02:10:15 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_str(int n, int sign)
{
	int		len;
	int		i;
	char	*str;

	len = ft_len(n) + sign;
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = 0;
	if (sign)
		str[i++] = '-';
	while (len >= 0 && n)
	{
		str[--len] = (n % 10) + '0';
		n = n / 10;
		if (len == 1 && sign)
			break ;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	str = ft_str(n, sign);
	return (str);
}
