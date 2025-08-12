NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm


SRC = src/main.c src/parsing/parsing_utils_1.c src/parsing/ext_read_line.c \
		libraries/libft/ft_memset.c libraries/libft/ft_strchr.c libraries/libft/ft_strlen.c \
		libraries/libft/ft_strnstr.c libraries/libft/get_next_line.c libraries/libft/get_next_line_utils.c \
		src/parsing/parse_metadata.c src/parsing/clean_up.c src/parsing/clean.c src/parsing/parse_color.c \
		libraries/libft/ft_split.c libraries/libft/ft_strtrim.c libraries/libft/ft_substr.c libraries/libft/ft_isdigit.c \
		libraries/libft/ft_strdup.c src/parsing/parse_texure.c libraries/libft/ft_strcmp.c libraries/libft/ft_atoi.c \
		src/parsing/map_border.c src/parsing/validate_map.c libraries/libft/ft_calloc.c src/parsing/fill_empty_spaces.c \
		src/game/collision.c src/game/exit.c src/game/image_utils.c src/game/key_handling.c src/parsing/parse_metadata_utils.c \
		src/game/player_movement.c src/game/setters.c src/game/utils.c src/game/drawing.c \
		src/game/getters.c src/game/initializer.c src/game/map_utils.c src/game/rendering.c src/game/update.c \
		src/parsing/parsing.c libraries/libft/ft_strncmp.c libraries/libft/ft_split_by_two.c\
		src/parsing/parse_color_3.c src/parsing/parse_color_utils.c src/parsing/parse_color_utils_2.c \
		# src/parsing/parsing 



OBJS = $(SRC:.c=.o)


SRCB = src/main.c src/parsing/parsing_utils_1.c src/parsing/ext_read_line.c \
		libraries/libft/ft_memset.c libraries/libft/ft_strchr.c libraries/libft/ft_strlen.c \
		libraries/libft/ft_strnstr.c libraries/libft/get_next_line.c libraries/libft/get_next_line_utils.c \
		src/parsing/parse_metadata.c src/parsing/clean_up.c src/parsing/clean.c src/parsing/parse_color.c \
		libraries/libft/ft_split.c libraries/libft/ft_strtrim.c libraries/libft/ft_substr.c libraries/libft/ft_isdigit.c \
		libraries/libft/ft_strdup.c src/parsing/parse_texure.c libraries/libft/ft_strcmp.c libraries/libft/ft_atoi.c \
		src/parsing/map_border.c src/parsing/validate_map.c libraries/libft/ft_calloc.c src/parsing/fill_empty_spaces.c \
		src/game/collision.c src/game/exit.c src/game/image_utils.c src/game/key_handling.c \
		src/game_bonus/player_movement.c src/game_bonus/setters.c src/game/utils.c src/game_bonus/drawing.c src/game_bonus/drawing_bonus.c\
		src/game/getters.c src/game/initializer.c src/game/map_utils.c src/game_bonus/rendering.c src/game/update.c \
		libraries/libft/ft_itoa.c src/parsing/parsing.c libraries/libft/ft_strncmp.c libraries/libft/ft_split_by_two.c src/parsing/parse_metadata_utils.c \
		src/parsing/parse_color_3.c src/parsing/parse_color_utils.c src/parsing/parse_color_utils_2.c 
OBJSB = $(SRCB:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX)

bonus : $(NAME)_bonus 

$(NAME)_bonus : $(OBJSB)
	@$(CC) $(CFLAGS) $(OBJSB) -o $(NAME)_bonus $(MLX)

clean :
	@rm -f $(OBJS) $(OBJSB)

fclean : clean
	@rm -f $(NAME) $(NAME)_bonus

re : fclean all
