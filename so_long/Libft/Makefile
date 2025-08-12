# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 03:55:26 by aes-sayo          #+#    #+#              #
#    Updated: 2023/11/23 03:55:49 by aes-sayo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_atoi.c ft_isprint.c ft_putchar_fd.c ft_striteri.c ft_strnstr.c ft_bzero.c \
	   ft_itoa.c ft_putendl_fd.c ft_strjoin.c ft_strrchr.c ft_calloc.c ft_memchr.c \
	   ft_putnbr_fd.c ft_strlcat.c ft_strtrim.c ft_isalnum.c ft_memcmp.c ft_putstr_fd.c \
	   ft_strlcpy.c ft_substr.c ft_isalpha.c ft_memcpy.c ft_split.c ft_strlen.c ft_tolower.c \
	   ft_isascii.c ft_memmove.c ft_strchr.c ft_strmapi.c ft_toupper.c ft_isdigit.c ft_memset.c \
	   ft_strdup.c ft_strncmp.c

OBJS = $(SRCS:.c=.o)
SRCSBONUS = ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
			ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJSBONUS = $(SRCSBONUS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(OBJS)

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)
	@ar -rcs $(NAME) $(OBJS)

bonus: $(OBJSBONUS) all

$(OBJSBONUS): $(SRCSBONUS)
	$(CC) $(CFLAGS) -c $(SRCSBONUS)
	ar -rcs $(NAME) $(OBJSBONUS)

clean:
	@rm -f $(OBJS) $(OBJSBONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY : fclean clean re all bonus
