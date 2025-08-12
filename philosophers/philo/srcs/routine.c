/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:05:20 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:05:22 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

void	print_status(long ms, t_philo *philo, char *str, int status)
{
	if (get_value(&philo->lock, &philo->is_full))
		return ;
	pthread_mutex_lock(&philo->param->print_lock);
	ms = (timestamp_in('m') - get_lvalue(&philo->param->lock,
				&philo->param->start_time));
	if (status == 0)
	{
		if (get_value(&philo->param->lock, &philo->param->exit))
		{
			pthread_mutex_unlock(&philo->param->print_lock);
			return ;
		}
		printf("%ld %d %s\n", ms, philo->id, str);
		set_value(&philo->param->lock, &philo->param->exit, 1);
		set_value(&philo->param->lock, &philo->param->end, 1);
	}
	else if (status == 1 && !get_value(&philo->param->lock, &philo->param->end))
		printf("%ld %d %s\n", ms, philo->id, str);
	pthread_mutex_unlock(&philo->param->print_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->lock);
	print_status(0, philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->fork_two->lock);
	print_status(0, philo, "has taken a fork", 1);
	set_lvalue(&philo->lock, &philo->last_eat, timestamp_in('m'));
	print_status(0, philo, "is eating", 1);
	sleep_for(philo->param->time_eat);
	pthread_mutex_unlock(&philo->fork_two->lock);
	pthread_mutex_unlock(&philo->fork_one->lock);
	pthread_mutex_lock(&philo->lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->lock);
	if (philo->param->limit_meals != -1
		&& philo->meal_count >= philo->param->limit_meals)
		set_value(&philo->lock, &philo->is_full, 1);
}

void	philo_sleep(t_philo *philo)
{
	print_status(0, philo, "is sleeping", 1);
	sleep_for(philo->param->time_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_value(&philo->param->lock, &philo->param->all_ready) == 0)
		;
	set_lvalue(&philo->lock, &philo->last_eat, get_lvalue(&philo->param->lock,
			&philo->param->start_time));
	if (philo->param->num_philos == 1)
		return (one_philo(philo));
	print_status(0, philo, "is thinking", 1);
	if (philo->id % 2 == 0)
		usleep(100);
	while (get_value(&philo->param->lock, &philo->param->end) == 0)
	{
		philo_eat(philo);
		if (philo->param->limit_meals != -1 && get_value(&philo->lock,
				&philo->is_full))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	philo_think(t_philo *philo)
{
	print_status(0, philo, "is thinking", 1);
	if (philo->param->num_philos % 2)
		usleep(1000);
}
