/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:05:27 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:05:29 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	sleep_for(long ms)
{
	long	start;

	start = timestamp_in('u');
	ms *= 1000;
	if (ms > 1000)
		usleep(ms - 1000);
	while (timestamp_in('u') - start < ms)
		;
}

long	timestamp_in(char c)
{
	struct timeval	tv;
	long			ret;

	gettimeofday(&tv, NULL);
	if (c == 'u')
		ret = tv.tv_usec + tv.tv_sec * 1000000;
	else
		ret = tv.tv_usec / 1000 + tv.tv_sec * 1000;
	return (ret);
}
