/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:32 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:57:36 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

long	ft_atol(char *str)
{
	long	res;
	long	sign;
	int		i;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '	')
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		++i;
	}
	return (res * sign);
}

void	free_stack(t_stack **a)
{
	t_stack	*tmp;

	tmp = *a;
	while (*a != NULL)
	{
		tmp = (*a)->next;
		free(*a);
		*a = tmp;
	}
}

int	ft_strcmp_1(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (s1[i] == s2[i]);
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
