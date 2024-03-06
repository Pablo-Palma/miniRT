NAME = miniRT
CC = gcc
CFLAGS =  -g3 -Wall -Wextra -Werror -Iinc -Iinc/libft/inc
MLX_DIR = mlx
SRCS_DIR = src
OBJS_DIR = obj
LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS_FILES = main.c setup.c events.c render.c init.c geometry.c colors.c lighting.c vector.c sphere.c
SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
MLX_LIB = $(MLX_DIR)/libmlx.dylib

##RULES

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@cp mlx/libmlx.dylib . ## Copiar la librería mlx en el directorio actual para la compilación.
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@echo "Libft compiled successfully!"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft
	@echo "miniRT compiled successfully!"

clean :
	@rm -f libmlx.dylib ## Borrar dicha librería.
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@echo "Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@make fclean -C $(LIBFT_DIR)
	@echo "Executable and object files removed!"

re: fclean all

.PHONY: all clean fclean re
