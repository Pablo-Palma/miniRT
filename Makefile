NAME = miniRT
CC = gcc
MLX_DIR = mlx
CFLAGS =  -g3 -Wall -Wextra -Werror -Iinc -Iinc/libft/inc -I$(MLX_DIR)
CFLAGS =  -g3 -Wall -Wextra -Werror -Iinc -Iinc/libft/inc
SRCS_DIR = src
OBJS_DIR = obj
LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
##SRCS_FILES = main.c setup.c events.c render.c init.c geometry.c colors.c lighting.c vector.c sphere.c plane.c shadow.c cylinder.c
SRCS_FILES =	main/main.c								\
				init/init.c								\
				window/setup.c window/events.c			\
				render/render.c render/colors.c			\
				geometry/vector.c geometry/sphere.c	geometry/plane.c geometry/cylinder.c	\
				light/lighting.c light/shadow.c			\
				utils/clean.c							\
				parser/parser.c parser/parser_utils.c parser/parser_elem.c \
				object.c object_constructors.c object_print.c
OBJS = $(SRCS_FILES:%.c=$(OBJS_DIR)/%.o)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
# OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.dylib
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

MLX_FLAGS_MAC = -L./inc/libft -lft -lmlx -framework OpenGL -framework AppKit

##RULES

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@cp mlx/libmlx.dylib . ## Copiar la librería mlx en el directorio actual para la compilación.
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@echo "Libft compiled successfully!"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft
	@echo "miniRT compiled successfully!"

mac: $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(SRCS) $(CFLAGS) $(MLX_FLAGS_MAC)
	@echo "miniRT compiled successfully on macOS!"

clean :
	@rm -f libmlx.dylib ## Borrar dicha librería.
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@echo "Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@make fclean -C $(LIBFT_DIR)
	@echo "Executable and object files removed!"

re: fclean all

.PHONY: all clean fclean re mac
