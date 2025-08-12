/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:57:59 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/03/05 16:58:01 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include "../libft/libft.h"
# include "./get_next_line/get_next_line_bonus.h"
# include <limits.h>
# include <stdlib.h>

typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}					t_stack;

typedef struct s_argv
{
	char			**split;
	struct s_argv	*next;
}					t_argv;

/*_______________________stack_functions________________________________*/

t_stack				*ft_new_node(int value);
void				ft_push_node(t_stack **stack_x, t_stack *node);
t_stack				*ft_last(t_stack *stack_x);
size_t				ft_stack_len(t_stack *stack_x);

/*_______________________argv_functions_________________________________*/

t_argv				*ft_new_argv(char *av);
void				ft_argv_add(t_argv	**head, t_argv *av);

/*_______________________subject_functions______________________________*/

void				ft_sa(t_stack **a);
void				ft_sb(t_stack **b);
void				ft_ss(t_stack **a, t_stack **b);
void				ft_pa(t_stack **a, t_stack **b);
void				ft_pb(t_stack **a, t_stack **b);
void				ft_ra(t_stack **a);
void				ft_rb(t_stack **b);
void				ft_rr(t_stack **a, t_stack **b);
void				ft_rra(t_stack **a);
void				ft_rrb(t_stack **b);
void				ft_rrr(t_stack **a, t_stack **b);

/*________________________stack_methods_________________________________*/

void				ft_swap(t_stack **stack_a);
void				ft_push(t_stack **from, t_stack **to);
void				ft_rotate(t_stack **stack_x);
void				ft_reverse_rotate(t_stack **stack_x);

/*_________________________check_functions______________________________*/

int					ft_is_sorted(t_stack *stack_x);
int					ft_is_duplicated(t_stack *a);
int					ft_check_error_stack(t_argv *av);
int					is_valid_argv(t_argv *split_av);

/*_________________________________utils________________________________*/

int					ft_init_stack_stack(t_stack **a, t_argv **av);
long				ft_atol(char *str);
int					ft_strcmp_1(char *s1, char *s2);

/*_______________________freeing_functions______________________________*/

int					ft_free_stack_print_error(t_stack **a);
void				free_stack(t_stack **a);
void				free_split_av(t_argv **av);

#endif
