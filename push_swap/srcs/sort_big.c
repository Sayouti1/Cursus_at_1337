/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:58:05 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:58:07 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	update_max_rank(t_stack **b, size_t *max_rank, size_t *max_index)
{
	t_stack	*tmp;
	size_t	i;

	tmp = *b;
	*max_index = tmp->index;
	*max_rank = 0;
	i = 0;
	while (tmp)
	{
		if (tmp->index > *max_index)
		{
			*max_index = tmp->index;
			*max_rank = i;
		}
		i++;
		tmp = tmp->next;
	}
}

int	*init_vars_get_arr(t_stack *a, int *range, size_t *stack_len, size_t *i)
{
	*stack_len = ft_stack_len(a);
	*range = get_range(a);
	*i = 0;
	return (get_sorted_arr(a));
}

int	ft_is_rev_sorted(t_stack **a, int *arr, size_t len)
{
	size_t	occ;
	size_t	i;
	t_stack	*tmp;
	size_t	j;

	occ = 0;
	i = len / 2;
	while (i < len)
	{
		j = len / 2;
		tmp = *a;
		while (tmp && j)
		{
			if (arr[i] == tmp->value)
				++occ;
			tmp = tmp->next;
			--j;
		}
		++i;
	}
	if (len == 100)
		return (occ >= (len / 2));
	else
		return (occ >= (len / 3));
}

int	ft_to_b(t_stack **a, t_stack **b)
{
	while (*a)
		ft_pb(a, b);
	return (1);
}

void	ft_sort_big(t_stack **a, t_stack **b, size_t *a_len)
{
	int		range;
	int		*arr;
	size_t	i;

	arr = init_vars_get_arr(*a, &range, a_len, &i);
	while (*a)
	{
		if (ft_stack_len(*a) == *a_len && ft_is_rev_sorted(a, arr, *a_len)
			&& ft_to_b(a, b))
			break ;
		if (i <= *a_len - 1 && (((*a)->value <= arr[i]) || ((range
						+ i <= *a_len - 1 && (*a)->value <= arr[range + i]))))
		{
			ft_pb(a, b);
			if ((*b)->value <= arr[i])
				ft_rb(b);
			else if ((*b)->next && (*b)->value < (*b)->next->value)
				ft_sb(b);
			i++;
		}
		else
			ft_ra(a);
	}
	free(arr);
	push_back_to_a(a, b);
}
