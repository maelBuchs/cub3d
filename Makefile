# Variables
NAME = cub3D

CC = gcc
 
CFLAGS = -Wall -Wextra -Werror -g

IFLAGS = -I ./includes

SRCS = main.c \
	   srcs/window.c \
	   srcs/parse_map.c \
	   srcs/init.c \
	   srcs/is_map_closed.c\
	   srcs/dda.c \
	   srcs/init_window.c \
	   srcs/render.c	\
	   srcs/update.c \
	   srcs/key.c \
	   srcs/init_textures.c \
	   srcs/utils.c \
	   srcs/math.c \
	   srcs/ray_casting_utils.c \
	   srcs/draw_textures.c 

OBJS = $(SRCS:.c=.o)

libft_DIR = libft

libft = $(libft_DIR)/libft.a

MLX_DIR = ./minilibx-linux 

MLX = -L./minilibx-linux -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(libft) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(libft) $(MLX)

$(libft):
	make -C $(libft_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(libft_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(libft_DIR)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) $(IFLAGS) -o $@ -c $<

.PHONY: all clean fclean re
