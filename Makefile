CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
RM = rm -f
CLIENT = client
SERVER = server

all: $(CLIENT) $(SERVER)

$(CLIENT): client.o utils.o $(LIBFT)
	$(CC) $(CFLAGS) client.o utils.o $(LIBFT) -o $(CLIENT)

$(SERVER): server.o utils.o $(LIBFT)
	$(CC) $(CFLAGS) server.o utils.o $(LIBFT) -o $(SERVER)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(MAKE) clean -C libft
	$(RM) *.o

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re
