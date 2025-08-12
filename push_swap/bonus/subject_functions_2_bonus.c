/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject_functions_2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:58:20 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:58:24 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_ra(t_stack **a)
{
	ft_rotate(a);
}

void	ft_rb(t_stack **b)
{
	ft_rotate(b);
}

void	ft_rr(t_stack **a, t_stack **b)
{
	ft_rotate(a);
	ft_rotate(b);
}

void	ft_rra(t_stack **a)
{
	ft_reverse_rotate(a);
}

void	ft_rrb(t_stack **b)
{
	ft_reverse_rotate(b);
}
