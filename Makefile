UNAME := $(shell uname)
NAME = miniRT
CC = gcc
MLX_DIR = mlx
CFLAGS = -Wall -Wextra -Werror -g3

SRCS_DIR = src
OBJS_DIR = obj
SRCS_FILES =	vector/vector.c	\
				light/lighting.c	\
				main/main.c	\
				object.c	\
				object_constructors.c	\
				object_intersect.c	\
				object_print.c	\
				object_trace.c	\
				object_normal.c	\
				ray.c			\
				render/colors.c	\
				render/render.c	\
				utils/clean.c	\
				window/events.c	\
				window/setup.c	\
				parser/parser_utils.c	\

SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS = $(SRCS_FILES:%.c=$(OBJS_DIR)/%.o)
# OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

LIBFT_DIR = inc/libft
ifeq ($(UNAME), Darwin)
    MLX_DIR := minilibx_opengl_20191021
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
    MLX_FLAGS := -L$(MLX_DIR) -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
endif
LIBS = $(LIBFT_FLAGS) $(MLX_FLAGS)



LIBFT = $(LIBFT_DIR)/libft.a
ifeq ($(UNAME), Darwin)
    MLX := $(MLX_DIR)/libmlx.dylib
else
    MLX := $(MLX_DIR)/libmlx.a
endif
LIBS = $(LIBFT_FLAGS) $(MLX_FLAGS)



ifeq ($(UNAME), Darwin)
    MLX_FILE := minilibx_opengl.tgz
else
    MLX_FILE := minilibx-linux.tgz
endif



##RULES

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@echo "Libft compiled successfully!"


$(MLX): $(MLX_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@echo "MLX compiled successfully!"

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(INCLUDE) $(LIBS)
	@echo "miniRT compiled successfully!"

clean :
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@make fclean -C $(LIBFT_DIR)
	@echo "Executable and object files removed!"

re: fclean all

unzip:
	@tar -xvf $(MLX_FILE)

up:
	@$(MAKE) -C $(MLX_DIR)

.PHONY: all clean fclean re mac
