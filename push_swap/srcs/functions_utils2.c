/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:12:19 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/06 00:12:21 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*get_sorted_arr(t_stack *a)
{
	int			*sorted_tab;
	t_stack		*tmp;
	size_t		i;

	i = 0;
	sorted_tab = (int *)malloc(sizeof(int) * ft_stack_len(a));
	if (!sorted_tab)
		return (NULL);
	tmp = a;
	while (tmp)
	{
		sorted_tab[i++] = tmp->value;
		tmp = tmp->next;
	}
	ft_selection_sort(sorted_tab, ft_stack_len(a));
	ft_set_indexes(a, sorted_tab, ft_stack_len(a));
	return (sorted_tab);
}

int	get_range(t_stack *a)
{
	size_t	length_a;

	length_a = ft_stack_len(a);
	if (length_a <= 25)
		return (7);
	else if (length_a <= 50)
		return (13);
	else if (length_a <= 100)
		return (14);
	else if (length_a <= 200)
		return (17);
	else if (length_a <= 550)
		return (28);
	else
		return (50);
}

int	get_max_value(t_stack **a)
{
	int		max;
	t_stack	*tmp;

	tmp = *a;
	max = tmp->value;
	while (tmp)
	{
		if (tmp->value > max)
			max = tmp->value;
		tmp = tmp->next;
	}
	return (max);
}

void	push_back_to_a(t_stack **a, t_stack **b)
{
	while (*b)
	{
		max_to_top(b);
		ft_pa(a, b);
	}
}

void	max_to_top(t_stack **b)
{
	size_t	b_length;
	size_t	max_index;
	size_t	max_rank;

	b_length = ft_stack_len(*b);
	update_max_rank(b, &max_rank, &max_index);
	while ((*b)->index != max_index)
	{
		if (max_rank <= (b_length / 2))
			ft_rb(b);
		else
			ft_rrb(b);
		update_max_rank(b, &max_rank, &max_index);
	}
}
