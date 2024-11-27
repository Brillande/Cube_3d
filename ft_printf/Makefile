NAME = libftprintf.a
SOURCES = \
	libftprintf.c utils.c utils1.c

OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar crs
all: libft $(NAME)

libft :
	@ $(MAKE) -C libft
$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) -Llibft -llibft $?

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re libft