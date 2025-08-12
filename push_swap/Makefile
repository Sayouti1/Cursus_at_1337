# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 02:55:39 by aes-sayo          #+#    #+#              #
#    Updated: 2024/02/25 21:30:16 by aes-sayo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=push_swap
BONUS=checker
CC=cc
CFLAGS=-Wall -Wextra -Werror

SRCS= srcs/push_swap.c srcs/algorithms_utils.c srcs/functions_utils.c srcs/functions_utils2.c srcs/other_functions.c srcs/stack_functions.c srcs/subject_functions_2.c srcs/subject_functions.c srcs/subject_functions_gen.c srcs/sort_big.c
OBJS=$(SRCS:.c=.o)
SRCSB= bonus/subject_functions_bonus.c bonus/subject_functions_2_bonus.c bonus/subject_functions_gen_bonus.c bonus/stack_functions_bonus.c bonus/other_functions_bonus.c bonus/functions_utils_bonus.c bonus/checker_bonus.c bonus/get_next_line/get_next_line_bonus.c bonus/get_next_line/get_next_line_utils_bonus.c 
OBJSB=$(SRCSB:.c=.o)

all: $(NAME)
bonus :	$(BONUS)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a

$(BONUS): $(OBJSB)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(BONUS) $(OBJSB) ./libft/libft.a
	
clean :
	$(MAKE) -C libft clean
	rm -f $(OBJS) $(OBJSB)

fclean : clean
	$(MAKE) -C libft fclean
	rm -f $(NAME) checker

re : fclean all

.PHONY: all clean fclean re
