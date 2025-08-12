NAME = webserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = src/main.cpp src/CPP/Request.cpp src/CPP/ServerRun.cpp src/CPP/utils.cpp \
 src/CPP/Client.cpp  src/CPP/Response.cpp src/CPP/CGIExecutor.cpp parse/config_parser.cpp \
 src/CPP/Request_p.cpp

OBJS = $(SRCS:src/%.cpp=objs/%.o)

all : $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

objs/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@rm -rf objs

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re run
