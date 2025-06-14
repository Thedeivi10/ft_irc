# Compiler and Flags
CXX     := c++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98

# Executable name
NAME    := irc_server

# Source files
SRCS    := main.cpp Server.cpp Client.cpp Helpers.cpp

# Object files
OBJS    := $(SRCS:.cpp=.o)

# Header dependencies
HEADERS := Server.hpp Client.hpp

# Default target
all: $(NAME)

# Linking
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation rule
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re