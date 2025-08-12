/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:05:12 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:05:15 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	*ft_monitor(void *arg)
{
	t_param	*param;
	int		i;
	int		j;

	param = (t_param *)arg;
	if (param->num_philos == 1)
		return (NULL);
	while (get_value(&param->lock, &param->all_ready) == 0)
		usleep(100);
	usleep(param->time_die * 1000);
	j = param->num_philos;
	i = 0;
	while (get_value(&param->lock, &param->end) == 0)
	{
		i = 0;
		while (i < j)
		{
			if (philo_died(&param->philo[i++]))
				return (NULL);
			usleep(100);
		}
		usleep(1000);
	}
	return (NULL);
}
