/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject_functions_gen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:58:38 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:58:40 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(t_stack **stack_x)
{
	t_stack	*tmp;

	if (ft_stack_len(*stack_x) < 2)
		return ;
	tmp = (*stack_x)->next;
	(*stack_x)->next = tmp->next;
	tmp->next = *stack_x;
	*stack_x = tmp;
}

void	ft_push(t_stack **from, t_stack **to)
{
	t_stack	*tmp;

	if (!(*from))
		return ;
	tmp = (*from)->next;
	(*from)->next = *to;
	*to = *from;
	*from = tmp;
}

void	ft_rotate(t_stack **stack_x)
{
	t_stack	*tmp;

	if (ft_stack_len(*stack_x) < 2)
		return ;
	tmp = *stack_x;
	*stack_x = (*stack_x)->next;
	tmp->next = NULL;
	ft_last(*stack_x)->next = tmp;
}

void	ft_reverse_rotate(t_stack **stack_x)
{
	t_stack	*tmp;
	t_stack	*last;

	if (ft_stack_len(*stack_x) < 2)
		return ;
	last = ft_last(*stack_x);
	tmp = *stack_x;
	while (tmp->next->next)
		tmp = tmp->next;
	tmp->next = NULL;
	last->next = *stack_x;
	*stack_x = last;
}

int	is_valid_argv(t_argv *split_av)
{
	t_argv	*tmp;

	tmp = split_av;
	while (tmp)
	{
		if (!tmp->split)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
