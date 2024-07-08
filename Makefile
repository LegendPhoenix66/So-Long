# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Header file
HEADER = so_long.h

# Source files
SRC = so_long.c check_args.c hook_handler.c image_utils.c close_helper.c map_utils.c player_movement.c update_images.c draw.c check_map.c validate_map.c can_reach.c handle_object.c check_interactions.c animate.c load_images.c

# Name of the executable
NAME = so_long

# Subfolder for object files
OBJDIR = obj/

# Object files for the server
OBJS = $(patsubst %.c,$(OBJDIR)%.o,$(SRC))

# MinilibX
MLX = minilibx-linux
MLX_LIB = $(addprefix $(MLX)/,libmlx.a)
MLX_INC = -I $(MLX)
MLX_LNK = -L $(MLX) -l mlx -lXext -lX11

# Rule for creating the executable
all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	make -C printf
	$(CC) $(CFLAGS) $(OBJS) printf/libftprintf.a $(MLX_LNK) -o $(NAME)

$(OBJDIR)%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

$(MLX_LIB):
	make -C $(MLX)

clean:
	make clean -C printf
	make clean -C $(MLX)
	rm -f $(OBJS) $(OBJS)

fclean: clean
	make fclean -C printf
	rm -f $(NAME) $(NAME)

re: fclean all

.PHONY: all clean fclean re