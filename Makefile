NAME_SERVER = server
NAME_CLIENT = client

SOURCES_SERVER = minitalk_server.c
SOURCES_CLIENT = minitalk_client.c

OBJECTS_SERVER = $(SOURCES_SERVER:.c=.o)
OBJECTS_CLIENT = $(SOURCES_CLIENT:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
PRINTF_DIR = printf

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

all: $(NAME_SERVER) $(NAME_CLIENT)

bonus: all

$(NAME_SERVER): $(OBJECTS_SERVER) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf

$(NAME_CLIENT): $(OBJECTS_CLIENT) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS_SERVER) $(OBJECTS_CLIENT)
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	rm -f $(LIBFT) $(PRINTF)

re: fclean all

.PHONY: all bonus clean fclean re libft printf
