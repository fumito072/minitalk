# NAME = minitalk.a
# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# SRCS = minitalk_server.c 
# OBJ = $(SRCS:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJ)
# 	ar rcs $(NAME) $(OBJ)

# clean:
# 	@echo "Cleaning object files..."
# 	rm -f $(OBJ)

# fclean: clean
# 	@echo "Cleaning $(NAME)..."
# 	rm -f $(NAME)

# re: fclean all

SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

bonus: server client

server: server.o libft
	$(CC) -o $@ $< -Llibft -lft

client: client.o libft
	$(CC) -o $@ $< -Llibft -lft

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean
	
fclean: clean
	rm -f server client libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re