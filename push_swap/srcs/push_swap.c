/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:50 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:57:52 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_free_stack_print_error(t_stack **a)
{
	free_stack(a);
	ft_putendl_fd("Error", 2);
	return (1);
}

t_argv	*ft_new_argv(char *av)
{
	t_argv	*argv;

	argv = (t_argv *)malloc(sizeof(t_argv));
	if (!argv)
		return (NULL);
	argv->split = ft_split(av, ' ');
	argv->next = NULL;
	return (argv);
}

void	ft_argv_add(t_argv	**head, t_argv *av)
{
	t_argv	*tmp;

	if (!*head)
	{
		*head = av;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = av;
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
	ft_sort_algo(&a, &b);
	return (0);
}
