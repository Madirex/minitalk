CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
RM = rm -f

all: client server

client: client.o utils.o $(LIBFT)
	$(CC) $(CFLAGS) client.o utils.o $(LIBFT) -o client

server: server.o utils.o $(LIBFT)
	$(CC) $(CFLAGS) server.o utils.o $(LIBFT) -o server

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(MAKE) clean -C libft
	$(RM) *.o

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) client server

re: fclean all

.PHONY: all clean fclean re