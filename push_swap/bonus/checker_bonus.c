/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:13:44 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/06 00:13:46 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	move_done(char *move, t_stack **a, t_stack **b)
{
	if (ft_strcmp_1(move, "sa\n"))
		return (ft_sa(a), 1);
	else if (ft_strcmp_1(move, "sb\n"))
		return (ft_sb(b), 1);
	else if (ft_strcmp_1(move, "ss\n"))
		return (ft_ss(a, b), 1);
	else if (ft_strcmp_1(move, "pa\n"))
		return (ft_pa(a, b), 1);
	else if (ft_strcmp_1(move, "pb\n"))
		return (ft_pb(a, b), 1);
	else if (ft_strcmp_1(move, "ra\n"))
		return (ft_ra(a), 1);
	else if (ft_strcmp_1(move, "rb\n"))
		return (ft_rb(b), 1);
	else if (ft_strcmp_1(move, "rr\n"))
		return (ft_rr(a, b), 1);
	else if (ft_strcmp_1(move, "rra\n"))
		return (ft_rra(a), 1);
	else if (ft_strcmp_1(move, "rrb\n"))
		return (ft_rrb(b), 1);
	else if (ft_strcmp_1(move, "rrr\n"))
		return (ft_rrr(a, b), 1);
	return (0);
}

void	ft_checker(t_stack **a, t_stack **b)
{
	size_t	a_length;
	char	*move;

	a_length = ft_stack_len(*a);
	move = get_next_line(0);
	while (move)
	{
		if (!move_done(move, a, b))
		{
			ft_putstr_fd("Error\n", 2);
			free(move);
			free_stack(b);
			free_stack(a);
			return ;
		}
		free(move);
		move = get_next_line(0);
	}
	if (ft_is_sorted(*a) && !ft_stack_len(*b))
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	free_stack(b);
	free_stack(a);
}

int	check_overflow(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		++i;
	while (str[i] == '0')
		++i;
	if (ft_strlen(str) - i > 10)
		return (1);
	return (0);
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

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	t_argv	*split_av;
	int		i;

	a = NULL;
	b = NULL;
	if (ac == 1)
		return (0);
	i = 1;
	split_av = ft_new_argv(av[i++]);
	while (i < ac)
		ft_argv_add(&split_av, ft_new_argv(av[i++]));
	if (!split_av || !is_valid_argv(split_av))
		return (free_split_av(&split_av), ft_putendl_fd("Error", 2), 0);
	if (ft_check_error_stack(split_av))
		return (free_split_av(&split_av), ft_putendl_fd("Error", 2), 0);
	if (ft_init_stack_stack(&a, &split_av))
		return (free_split_av(&split_av), ft_putendl_fd("Error", 2), 0);
	if (ft_is_duplicated(a))
		return (ft_free_stack_print_error(&a));
	ft_checker(&a, &b);
	return (0);
}
