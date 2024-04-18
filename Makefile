UNAME := $(shell uname)
NAME = miniRT
CC = gcc
MLX_DIR = mlx
CFLAGS = -Wall -Wextra -Werror -Iinc -o3

SRCS_DIR = src
OBJS_DIR = obj
LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_FILES =	main/main.c								\
				window/setup.c window/events.c			\
				render/render.c			\
				render/colors.c			\
				classes/vector/vector_1.c	\
				classes/vector/vector_2.c	\
				classes/vector/vector_3.c	\
				classes/vector/vector_4.c	\
				light/lighting.c						\
				utils/clean.c							\
				classes/object/object.c \
				classes/object/object_constructors.c \
				classes/object/object_intersect.c \
				classes/object/object_normal.c \
				classes/object/object_print.c \
				classes/object/object_trace.c \
				classes/object/object_check.c \
				classes/object/object_check_attr.c \
				classes/object/object_constructor_attr.c \
				classes/ray/ray.c \
				utils/extra_list.c \
				parser/parser.c \
				parser/parser_utils.c


BONUS_FILES =	bonus/checkerboard_bonus.c bonus/plane_bonus.c	\
				bonus/sphere_bonus.c bonus/cylinder_bonus.c		\
				bonus/cylinder_utils_bonus.c					\
				bonus/reflection_bonus.c bonus/color_bonus.c\
				main/main.c								\
				window/setup.c window/events.c			\
				render/render.c render/colors.c			\
				vector/vector.c							\
				light/lighting.c light/shadow.c			\
				utils/clean.c							\
				classes/object/object.c \
				classes/object/object_constructors.c \
				classes/object/object_intersect.c \
				classes/object/object_normal.c \
				classes/object/object_print.c \
				classes/object/object_trace.c \
				classes/ray/ray.c \
				utils/extra_list.c


BONUS_OBJS = $(BONUS_FILES:%.c=$(OBJS_DIR)/%.o)
OBJS = $(SRCS_FILES:%.c=$(OBJS_DIR)/%.o)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
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

reflect: CFLAGS += -D MAX_REFLECT_LEVEL=1
reflect: re

bonus: CFLAGS += -D BONUS -Iinc/bonus
bonus: $(LIBFT) $(BONUS_OBJS)
	@$(CC) -o $(NAME) $(BONUS_OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft
	@echo "miniRT with bonus compiled successfully!"

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
