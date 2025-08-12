/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:32 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:57:36 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_atol(char *str)
{
	long	res;
	long	sign;
	int		i;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '	')
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		++i;
	}
	return (res * sign);
}

void	free_stack(t_stack **a)
{
	t_stack	*tmp;

	tmp = *a;
	while (*a != NULL)
	{
		tmp = (*a)->next;
		free(*a);
		*a = tmp;
	}
}

size_t	ft_index_of(int *arr, int x, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (arr[i] == x)
			return (i);
		i++;
	}
	return (0);
}

void	ft_set_indexes(t_stack *a, int *arr, size_t size)
{
	t_stack	*tmp;

	tmp = a;
	while (tmp)
	{
		tmp->index = ft_index_of(arr, tmp->value, size);
		tmp = tmp->next;
	}
}

int	ft_get_min(t_stack *a)
{
	int	min;

	min = a->value;
	while (a)
	{
		if (a->value < min)
			min = a->value;
		a = a->next;
	}
	return (min);
}
