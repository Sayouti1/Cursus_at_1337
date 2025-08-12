NAME = minishell 
CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRCS= srcs/main.c \
	srcs/execution/builtin/cd.c srcs/execution/builtin/env.c srcs/execution/builtin/pwd.c srcs/execution/builtin/export.c srcs/execution/builtin/export_2.c \
	srcs/execution/builtin/exit.c srcs/execution/builtin/unset.c srcs/execution/builtin/echo.c srcs/execution/builtin/exec_builtin.c \
	srcs/execution/utils/free.c srcs/execution/utils/redirection.c srcs/execution/utils/exec.c srcs/execution/utils/checkers.c srcs/execution/utils/free_2.c \
	srcs/execution/utils/token_to_command.c srcs/execution/utils/token_to_command_2.c srcs/execution/utils/garbage_collector.c srcs/execution/utils/pipe_utils.c \
	srcs/execution/utils/getters.c srcs/execution/utils/setters.c srcs/execution/utils/split.c srcs/execution/utils/heredoc_expand.c \
	srcs/execution/utils/utils.c srcs/execution/utils/pipe_exec.c srcs/execution/utils/signal.c srcs/execution/utils/heredoc.c \
	srcs/execution/utils/length.c srcs/execution/utils/str_utils.c srcs/execution/builtin/env_2.c srcs/execution/utils/utils_2.c \
	srcs/parsing/check_input/check_error_utils.c srcs/parsing/check_input/error_input.c srcs/parsing/expand/expand_utils.c \
	srcs/parsing/expand/expand.c srcs/parsing/lexer/lexer_utils.c srcs/parsing/lexer/lexer.c srcs/more_utils.c srcs/parsing/expand/more_utils_expand.c \
	srcs/utils.c srcs/just_test_utils.c srcs/parsing/check_input/split_expand.c \

OBJS=$(SRCS:.c=.o)
LIBFT= Libft/libft.a
all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C Libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	clear

clean :
	@$(MAKE) -C Libft clean
	@rm -f $(OBJS)
	@clear

fclean : clean
	@$(MAKE) -C Libft fclean
	@rm -f $(NAME)
	@clear

re : fclean all

.PHONY: all clean fclean re













