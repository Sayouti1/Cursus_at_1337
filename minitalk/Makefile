# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 15:05:58 by aes-sayo          #+#    #+#              #
#    Updated: 2024/03/21 17:40:17 by aes-sayo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minitalk
CC= cc
CFLAGS= -Wall -Wextra -Werror
S_SRCS= srcs/server.c
C_SRCS= srcs/client.c
SBONUS_SRCS= bonus/server_bonus.c
CBONUS_SRCS= bonus/client_bonus.c
LIBFT_SRCS= utils/ft_atoi.c utils/ft_putchar_fd.c utils/ft_putnbr_fd.c utils/ft_putstr_fd.c utils/ft_strlen.c
S_OBJS= $(S_SRCS:.c=.o)
C_OBJS= $(C_SRCS:.c=.o)
SBONUS_OBJS= $(SBONUS_SRCS:.c=.o)
CBONUS_OBJS= $(CBONUS_SRCS:.c=.o)
LIBFT_OBJS= $(LIBFT_SRCS:.c=.o)


all: $(NAME)

$(NAME): server client
bonus: server_bonus client_bonus

server : $(S_OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) $(LIBFT_OBJS) $(S_OBJS) -o server
client : $(C_OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) $(LIBFT_OBJS) $(C_OBJS) -o client

server_bonus : $(SBONUS_OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) $(LIBFT_OBJS) $(SBONUS_OBJS) -o server_bonus
client_bonus : $(CBONUS_OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) $(LIBFT_OBJS) $(CBONUS_OBJS) -o client_bonus

clean:
	rm -f $(C_OBJS) $(LIBFT_OBJS) $(S_OBJS) $(SBONUS_OBJS) $(CBONUS_OBJS)
fclean: clean
	rm -f server client server_bonus client_bonus
re: fclean all

.PHONY: all clean fclean re