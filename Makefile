NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilib/libft -Ilib/minilibx-linux

LIBFT = lib/libft/libft.a
MLX = lib/minilibx-linux/libmlx_Linux.a
MLXFLAGS = -Llib/minilibx-linux -lmlx_Linux -lXext -lX11 -lm

SRCS = main.c \
	src/parser/parse_args.c src/parser/error.c src/parser/read_file.c \
	src/parser/config.c src/parser/config_dispatch.c \
	src/parser/config_textures.c src/parser/config_color.c \
	src/parser/map.c src/parser/map_charset.c \
	src/parser/flood.c src/parser/flood_utils.c \
	src/window/window.c src/window/textures.c \
	src/hooks/hooks.c src/hooks/keys.c src/hooks/move.c src/hooks/cleanup.c \
	src/game/raycast.c src/game/raycast_dda.c \
	src/game/raycast_draw.c src/game/raycast_pixel.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	$(MAKE) -C lib/libft

$(MLX):
	$(MAKE) -C lib/minilibx-linux

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C lib/libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re
