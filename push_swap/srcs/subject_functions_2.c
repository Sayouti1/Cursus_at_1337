/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject_functions_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:58:20 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:58:24 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_ra(t_stack **a)
{
	if (!*a)
		return ;
	ft_rotate(a);
	ft_putstr_fd("ra\n", 1);
}

void	ft_rb(t_stack **b)
{
	if (!*b)
		return ;
	ft_rotate(b);
	ft_putstr_fd("rb\n", 1);
}

void	ft_rr(t_stack **a, t_stack **b)
{
	if (!*a && !*b)
		return ;
	ft_rotate(a);
	ft_rotate(b);
	ft_putstr_fd("rr\n", 1);
}

void	ft_rra(t_stack **a)
{
	if (!*a)
		return ;
	ft_reverse_rotate(a);
	ft_putstr_fd("rra\n", 1);
}

void	ft_rrb(t_stack **b)
{
	if (!*b)
		return ;
	ft_reverse_rotate(b);
	ft_putstr_fd("rrb\n", 1);
}
