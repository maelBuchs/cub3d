# Variables
NAME = cub3D

CC = clang
 
CFLAGS = -Wall -Wextra -Werror -g -O3 -ffast-math -fopenmp
CFLAGS += -I ./includes
LDFLAGS =

OBJS_DIR = objs
SRCS_DIR = srcs

SRCS = main.c \
	   window.c \
	   parse_map.c \
	   init.c \
	   is_map_closed.c\
	   dda.c \
	   init_window.c \
	   render.c	\
	   update.c \
	   key.c \
	   init_textures.c \
	   utils.c \
	   math.c \
	   ray_casting_utils.c \
	   draw_textures.c \
	   exit.c \
	   get_player_pos.c

OBJS := $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LDFLAGS += $(LIBFT)

MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
CFLAGS += -I$(MLX_DIR)
LDFLAGS += $(MLX) -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS)

$(LIBFT):
	make -j -C $(LIBFT_DIR)

$(MLX):
	make -j -C $(MLX_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
