# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -Ilibft

# Header file
HEADER = ft_printf.h

# Source files for the mandatory part
SRC = ft_printf.c ft_printf_print.c ft_printf_print_numbers.c ft_printf_conversions.c

# Subfolder for object files
OBJDIR = obj/

# Object files for the mandatory part
OBJS = $(addprefix $(OBJDIR),$(notdir $(SRC:.c=.o)))

# Name of the library
NAME = libftprintf.a

# Rule for creating the library
all: $(NAME)

# Rule for creating the bonus library
bonus: all

$(NAME): $(OBJS)
	make -C libft
	mkdir -p $(OBJDIR)
	cd $(OBJDIR) && ar -x ../libft/libft.a
	ar rcs $(NAME) $(OBJS) $(OBJDIR)/*.o

$(OBJDIR)%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
