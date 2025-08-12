/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:00:59 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/07/07 22:01:05 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	lock;

}					t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long			last_eat;
	int				meal_count;
	int				is_full;
	t_fork			*fork_one;
	t_fork			*fork_two;
	pthread_mutex_t	lock;
	struct s_param	*param;
}					t_philo;

typedef struct s_param
{
	int				num_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				limit_meals;
	long			start_time;
	int				all_ready;
	int				end;
	int				exit;
	t_philo			*philo;
	t_fork			*fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	print_lock;
	pthread_t		monitor;

}					t_param;

long				get_lvalue(pthread_mutex_t *lock, long *val);
int					get_value(pthread_mutex_t *lock, int *val);
void				set_lvalue(pthread_mutex_t *lock, long *var, long val);
void				set_value(pthread_mutex_t *lock, int *var, int val);

int					create_threads(t_param *param);
int					init_philos(t_param *param);
int					init_fork(t_param *param, int i);
int					init_philo_val(t_param *param, int i);
int					init_param(int ac, char **av, t_param *param);

void				*one_philo(t_philo *philo);

void				*ft_monitor(void *arg);

void				print_status(long ms, t_philo *philo, char *str,
						int status);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				*routine(void *arg);
void				philo_think(t_philo *philo);

void				sleep_for(long ms);
long				timestamp_in(char c);

int					ft_isdigit(char c);
int					ft_isspace(char c);
int					ft_strlen(char *s);
long				ft_atol(char *str);
int					philo_died(t_philo *philo);

#endif
