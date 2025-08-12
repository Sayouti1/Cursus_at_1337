/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:01:17 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:01:19 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

long	get_lvalue(pthread_mutex_t *lock, long *val)
{
	long	x;

	pthread_mutex_lock(lock);
	x = *val;
	pthread_mutex_unlock(lock);
	return (x);
}

int	get_value(pthread_mutex_t *lock, int *val)
{
	int	x;

	pthread_mutex_lock(lock);
	x = *val;
	pthread_mutex_unlock(lock);
	return (x);
}

void	set_lvalue(pthread_mutex_t *lock, long *var, long val)
{
	pthread_mutex_lock(lock);
	*var = val;
	pthread_mutex_unlock(lock);
}

void	set_value(pthread_mutex_t *lock, int *var, int val)
{
	pthread_mutex_lock(lock);
	*var = val;
	pthread_mutex_unlock(lock);
}
