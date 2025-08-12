# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 10:04:32 by aes-sayo          #+#    #+#              #
#    Updated: 2024/07/10 10:04:36 by aes-sayo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/getters_setters.c  srcs/main.c  srcs/routine.c srcs/init_param.c srcs/utils.c srcs/time.c srcs/monitor.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	@rm -f $(OBJS)
	@rm -f test

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
