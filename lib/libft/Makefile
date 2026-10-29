NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

CTYPE = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_toupper.c ft_tolower.c

MEMORY = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c ft_calloc.c

STRING = ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_strnstr.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c

CONVERT = ft_atoi.c ft_itoa.c

PUT = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

PRINTF = ft_printf.c ft_putchar.c ft_putstr.c ft_putunbr.c ft_putnbr.c \
	ft_puthex.c ft_putptr.c

GNL = get_next_line.c get_next_line_utils.c

LIST = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SRCS = $(addprefix ctype/, $(CTYPE)) $(addprefix memory/, $(MEMORY)) \
	$(addprefix string/, $(STRING)) $(addprefix convert/, $(CONVERT)) \
	$(addprefix put/, $(PUT)) $(addprefix printf/, $(PRINTF)) \
	$(addprefix gnl/, $(GNL))
BONUS_SRCS = $(addprefix list/, $(LIST))

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

ifeq ($(findstring bonus,$(MAKECMDGOALS)),bonus)
	OBJS += $(BONUS_OBJS)
endif

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c libft.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
