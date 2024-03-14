UNAME := $(shell uname)
NAME = miniRT
CC = gcc
MLX_DIR = mlx
CFLAGS = -Wall -Wextra -Werror -g3

SRCS_DIR = src
OBJS_DIR = obj
SRCS_FILES =	main/main.c								\
				init/init.c								\
				window/setup.c window/events.c			\
				render/render.c render/colors.c			\
				geometry/vector.c geometry/sphere.c	geometry/plane.c geometry/cylinder.c	\
				light/lighting.c light/shadow.c			\
				utils/clean.c							\
				parser/parser.c parser/parser_utils.c parser/parser_elem.c \
				object.c object_constructors.c object_print.c
SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS = $(SRCS_FILES:%.c=$(OBJS_DIR)/%.o)
# OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

LIBFT_DIR = inc/libft
ifeq ($(UNAME), Darwin)
    MLX_DIR := mlx
else
    MLX_DIR := minilibx-linux
endif

## -I
HEADERS = -Iinc
LIB_INC = -I$(LIBFT_DIR)/inc
MLX_INC = -I$(MLX_DIR)
INCLUDE = $(HEADERS) $(LIB_INC) $(MLX_INC)

## -L
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
ifeq ($(UNAME), Darwin)
    MLX_FLAGS := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
    MLX_FLAGS := -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
endif
LIBS = $(LIBFT_FLAGS) $(MLX_FLAGS)




LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.dylib
ifeq ($(UNAME), Darwin)
    MLX := $(MLX_DIR)/libmlx.dylib
else
    MLX := $(MLX_DIR)/libmlx_Linux.a
endif
LIBS = $(LIBFT_FLAGS) $(MLX_FLAGS)

##RULES

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@cp mlx/libmlx.dylib . ## Copiar la librería mlx en el directorio actual para la compilación.
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@echo "Libft compiled successfully!"

$(MLX):
	@$(MAKE) bonus -C $(MLX_DIR)
	@echo "MLX compiled successfully!"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(INCLUDE) $(LIBS)
	@echo "miniRT compiled successfully!"

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
