/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:17:39 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:05:07 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->lock);
	print_status(0, philo, "has taken a fork", 1);
	sleep_for(philo->param->time_die);
	pthread_mutex_unlock(&philo->fork_one->lock);
	print_status(0, philo, "\033[1;31mdied\033[0m", 0);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_param	param;

	if (ac != 5 && ac != 6)
		return (1);
	param.all_ready = 0;
	param.end = 0;
	param.exit = 0;
	if (init_param(ac, av, &param))
		return (0);
	init_philos(&param);
	free(param.fork);
	free(param.philo);
	return (0);
}
