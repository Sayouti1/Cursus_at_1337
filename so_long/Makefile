# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 19:37:48 by aes-sayo          #+#    #+#              #
#    Updated: 2024/02/08 16:59:53 by aes-sayo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRCS = srcs/main.c srcs/so_long_utils.c srcs/check_functions.c srcs/map_functions.c srcs/map_utils.c srcs/moves_functions.c srcs/validation_functions.c srcs/free_functions.c
OBJS = $(SRCS:.c=.o)
SRCSB = bonus/main_bonus.c bonus/so_long_utils_bonus.c bonus/check_functions_bonus.c bonus/map_functions_bonus.c bonus/map_utils_bonus.c bonus/moves_functions_bonus.c bonus/validation_functions_bonus.c bonus/free_functions_bonus.c
OBJSB = $(SRCSB:.c=.o)
CC = cc
LIBFT = ./Libft/libft.a
CFLAGS = -Wall -Wextra -Werror
XFLAGS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C Libft
	$(CC) $(CFLAGS) $(OBJS)  $(XFLAGS) -o $(NAME) $(LIBFT)

bonus : $(OBJSB)
	$(MAKE) -C Libft
	$(CC) $(CFLAGS) $(OBJSB)  $(XFLAGS) -o $(NAME) $(LIBFT)
	
clean:
	$(MAKE) -C Libft clean
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	$(MAKE) -C Libft fclean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re