/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subject_functions_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:58:31 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:58:33 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_sa(t_stack **a)
{
	ft_swap(a);
}

void	ft_sb(t_stack **b)
{
	ft_swap(b);
}

void	ft_ss(t_stack **a, t_stack **b)
{
	ft_swap(a);
	ft_swap(b);
}

void	ft_pa(t_stack **a, t_stack **b)
{
	ft_push(b, a);
}

void	ft_pb(t_stack **a, t_stack **b)
{
	ft_push(a, b);
}
