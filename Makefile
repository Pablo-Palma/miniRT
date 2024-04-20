NAME = miniRT
CC = gcc
CFLAGS =  -g3 -Wall -Wextra -Werror -Iinc -Iinc/libft/inc -I/usr/include/mlx
SRCS_DIR = src
OBJS_DIR = obj
LIBFT_DIR = inc/libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS_FILES =	main/main.c								\
				window/setup.c window/events.c			\
				render/render.c			\
				render/compute_ray.c	\
				render/colors.c			\
				classes/vector/vector_1.c	\
				classes/vector/vector_2.c	\
				classes/vector/vector_3.c	\
				classes/vector/vector_4.c	\
				light/lighting.c						\
				utils/clean.c							\
				classes/object/object.c \
				classes/object/object_constructor.c \
				classes/object/object_constructor2.c \
				classes/object/object_intersect.c \
				classes/object/object_intersect2.c \
				classes/object/object_method.c \
				classes/object/object_method2.c \
				classes/object/object_normal.c \
				classes/object/object_print.c \
				classes/object/object_print2.c \
				classes/object/object_check.c \
				classes/object/object_check2.c \
				classes/object/object_check_attr.c \
				classes/object/object_constructor_attr.c \
				classes/object/object_checkerboard.c \
				classes/ray/ray1.c \
				classes/ray/ray2.c \
				classes/ray/ray3.c \
				utils/extra_list.c \
				utils/bhaskara.c \
				parser/parser.c \
				parser/parser_utils.c
BONUS_OBJS = $(BONUS_FILES:%.c=$(OBJS_DIR)/%.o)
OBJS = $(SRCS_FILES:%.c=$(OBJS_DIR)/%.o)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
# OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.dylib
MLX_FLAGS =  -lmlx -framework OpenGL -framework AppKit

##RULES

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@echo "Libft compiled successfully!"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft
	@echo "miniRT compiled successfully!"

bonus: CFLAGS += -D BONUS -Iinc/bonus
bonus: $(LIBFT) $(BONUS_OBJS)
	@$(CC) -o $(NAME) $(BONUS_OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft
	@echo "miniRT with bonus compiled successfully!"

clean :
	@rm -rf $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@make fclean -C $(LIBFT_DIR)
	@echo "Executable and object files removed!"

re: fclean all

.PHONY: all clean fclean re mac
