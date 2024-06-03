# Variables
NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c 
OBJS = $(SRCS:.c=.o)
libft_DIR = libft
libft = $(libft_DIR)/libft.a
MLX_DIR = ./minilibx-linux  # Remplacez par le chemin correct vers la MinilibX
MLX = -L./minilibx-linux -lmlx -lX11 -lXext -lm

# Règles
all: $(NAME)

$(NAME): $(libft) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(libft) $(MLX)

$(libft):
	make -C $(libft_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(libft_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(libft_DIR)

re: fclean all

# Règles de dépendances
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -o $@ -c $<

.PHONY: all clean fclean reNAME =	cub3d

CC = gcc
# CFLAGS = -g
CFLAGS = -Wall -Wextra -Werror -g
MLX = -L./minilibx-linux -lmlx -lX11 -lXext -lm
RM = rm -rf
HEAD = includes/cub3d.h
SRCS = 	main.c

OBJS = $(SRCS:.c=.o)

TOTAL_FILES = $(words $(SRCS))

all:			$(NAME)
				@clear
				@echo "Compilation terminée";

$(NAME):		$(OBJS)
				make --no-print-directory -C libft/
				make --no-print-directory -C minilibx-linux/
#				gcc a.out -lm -I . -I ./libft -L ./libft -lft -I ./minilibx-linux -L ./minilibx-linux -mlx_Linux -lXext -lX11
				@$(CC) -o $(NAME)  $(HEAD) $(OBJS) $(CFLAGS) $(MLX) libft/libft.a minilibx-linux/libmlx.a

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:			
				make clean --no-print-directory -C  libft/
				make clean --no-print-directory -C minilibx-linux/
				@$(RM) $(OBJS)
				@clear
				@echo "Clean OK";


fclean: 		clean
				@$(RM) $(NAME) libft/libft.a libmlx_Linux.a
				@clear
				@echo "Full Clean OK ";

re: 			fclean all

.PHONY:			all clean fclean re