/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:58:31 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:58:33 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sa(t_stack **a)
{
	if (!*a)
		return ;
	ft_swap(a);
	ft_putstr_fd("sa\n", 1);
}

void	ft_sb(t_stack **b)
{
	if (!*b)
		return ;
	ft_swap(b);
	ft_putstr_fd("sb\n", 1);
}

void	ft_ss(t_stack **a, t_stack **b)
{
	if (!*a && !*b)
		return ;
	ft_swap(a);
	ft_swap(b);
	ft_putstr_fd("ss\n", 1);
}

void	ft_pa(t_stack **a, t_stack **b)
{
	if (!*b)
		return ;
	ft_push(b, a);
	ft_putstr_fd("pa\n", 1);
}

void	ft_pb(t_stack **a, t_stack **b)
{
	if (!*a)
		return ;
	ft_push(a, b);
	ft_putstr_fd("pb\n", 1);
}
