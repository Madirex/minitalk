SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

server: server.o libft
	$(CC) -o $@ server.o -Llibft -lft

client: client.o libft
	$(CC) -o $@ client.o -Llibft -lft

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

libft:
	make -C libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean

fclean: clean
	rm -f server client libft/libft.a

re: fclean all

.PHONY: all clean fclean re libft