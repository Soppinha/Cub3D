NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -std=gnu17 -Iincludes -Ilib/libft -Ilib/minilibx-linux

LIBFT = lib/libft/libft.a
MLX = lib/minilibx-linux/libmlx_Linux.a
MLXFLAGS = -Llib/minilibx-linux -lmlx_Linux -lXext -lX11 -lm

SRCS_COMMON = main.c \
	src/parser/parse_args.c src/parser/error.c src/parser/read_file.c \
	src/parser/config.c src/parser/config_dispatch.c \
	src/parser/config_textures.c src/parser/config_color.c \
	src/parser/map.c src/parser/map_charset.c \
	src/parser/flood.c src/parser/flood_utils.c \
	src/window/window.c src/window/textures.c \
	src/hooks/hooks.c src/hooks/keys.c src/hooks/move.c src/hooks/cleanup.c \
	src/game/raycast.c src/game/raycast_dda.c \
	src/game/raycast_draw.c src/game/raycast_pixel.c
SRCS = $(SRCS_COMMON) src/hooks/collision.c src/hooks/mouse.c
SRCS_BONUS = $(SRCS_COMMON) src/hooks/collision_bonus.c \
	src/hooks/mouse_bonus.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

all: $(NAME)

$(LIBFT):
	$(MAKE) -C lib/libft

$(MLX):
	$(MAKE) -C lib/minilibx-linux

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(MLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT) $(MLX) $(MLXFLAGS)

$(OBJ_DIR)/%.o: %.c includes/cub3d.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C lib/libft clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C lib/libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
