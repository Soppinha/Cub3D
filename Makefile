NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft

LIBFT = libft/libft.a

SRCS = main.c parse_args.c error.c read_file.c config.c map.c flood.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
