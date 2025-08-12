/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:59 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:58:01 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <limits.h>
# include <stdlib.h>

typedef struct s_stack
{
	int				value;
	size_t			index;
	struct s_stack	*next;
}					t_stack;

typedef struct s_argv
{
	char			**split;
	struct s_argv	*next;
}					t_argv;

/*_______________________stack_functions________________________________*/

t_stack		*ft_new_node(int value);
void		ft_push_node(t_stack **stack_x, t_stack *node);
void		ft_swap(t_stack **stack_a);
void		ft_push(t_stack **from, t_stack **to);
void		ft_rotate(t_stack **stack_x);
void		ft_reverse_rotate(t_stack **stack_x);

/*_______________________subject_functions______________________________*/

void		ft_sa(t_stack **a);
void		ft_sb(t_stack **b);
void		ft_ss(t_stack **a, t_stack **b);
void		ft_pa(t_stack **a, t_stack **b);
void		ft_pb(t_stack **a, t_stack **b);
void		ft_ra(t_stack **a);
void		ft_rb(t_stack **b);
void		ft_rr(t_stack **a, t_stack **b);
void		ft_rra(t_stack **a);
void		ft_rrb(t_stack **b);
void		ft_rrr(t_stack **a, t_stack **b);

/*_______________________getters________________________________________*/

size_t		ft_get_index(t_stack *a, int value);
int			ft_get_min(t_stack *a);
int			get_max_value(t_stack **a);
int			*get_sorted_arr(t_stack *a);
int			get_range(t_stack *a);
size_t		ft_index_of(int *arr, int x, size_t size);
t_stack		*ft_last(t_stack *stack_x);
size_t		ft_stack_len(t_stack *stack_x);

/*_______________________check_functions________________________________*/
int			ft_is_sorted(t_stack *stack_x);
int			ft_is_duplicated(t_stack *a);
int			ft_check_error_stack(t_argv *av);
int			is_valid_argv(t_argv *split_av);

/*_______________________sort_algo.c____________________________________*/

void		ft_sort_algo(t_stack **a, t_stack **b);
void		ft_sort_big(t_stack **a, t_stack **b, size_t *stack_len);
void		ft_sort_three(t_stack **a);
void		ft_sort_min(t_stack **a, t_stack **b);
void		ft_selection_sort(int *arr, size_t size);

/*_______________________utils__________________________________________*/

long		ft_atol(char *str);
void		push_back_to_a(t_stack **a, t_stack **b);
void		max_to_top(t_stack **b);
void		update_max_rank(t_stack **b, size_t *max_rank, size_t *max_index);
void		ft_set_indexes(t_stack *a, int *arr, size_t size);
int			ft_init_stack_stack(t_stack **a, t_argv **av);

/*_______________________freeing_functions______________________________*/

void		free_stack(t_stack **a);
void		free_split_av(t_argv **av);

#endif
