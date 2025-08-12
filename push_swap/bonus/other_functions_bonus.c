/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:42 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:57:45 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	ft_check_error_stack(t_argv *av)
{
	size_t	i;
	size_t	j;

	while (av)
	{
		i = 0;
		while (av->split && av->split[i])
		{
			j = 0;
			while (av->split[i][j])
			{
				if (!ft_isdigit(av->split[i][j]) && (av->split[i][j] != '-'
						&& av->split[i][j] != '+'))
					return (1);
				if ((av->split[i][j] == '-' || av->split[i][j] == '+') && (j > 0
				|| !av->split[i][j + 1] || (av->split[i][j + 1]
				&& !ft_isdigit(av->split[i][j + 1]))))
					return (1);
				++j;
			}
			++i;
		}
		av = av->next;
	}
	return (0);
}

void	free_split_av(t_argv **av)
{
	t_argv	*tmp;
	size_t	i;

	tmp = *av;
	while (*av)
	{
		i = 0;
		while ((*av)->split && (*av)->split[i])
			free((*av)->split[i++]);
		free((*av)->split);
		tmp = (*av)->next;
		free(*av);
		*av = tmp;
	}
}

int	ft_init_stack_stack(t_stack **a, t_argv **av)
{
	size_t		i;
	t_argv		*tmp;

	tmp = *av;
	while (tmp)
	{
		i = 0;
		while (tmp->split && tmp->split[i])
		{
			if (ft_atol(tmp->split[i]) > INT_MAX
				|| ft_atol(tmp->split[i]) < INT_MIN)
			{
				free_stack(a);
				return (1);
			}
			ft_push_node(a, ft_new_node(ft_atol(tmp->split[i])));
			++i;
		}
		tmp = tmp->next;
	}
	free_split_av(av);
	return (0);
}

int	ft_is_duplicated(t_stack *a)
{
	t_stack	*tmp;

	while (a)
	{
		tmp = a->next;
		while (tmp)
		{
			if (a->value == tmp->value)
				return (1);
			tmp = tmp->next;
		}
		a = a->next;
	}
	return (0);
}

int	ft_free_stack_print_error(t_stack **a)
{
	free_stack(a);
	ft_putendl_fd("Error", 2);
	return (1);
}
