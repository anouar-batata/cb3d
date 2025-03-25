NAME = cub3D

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
# Directories
SRC_DIR = src
SRC_DIR_LIBFT = src/libft
SRC_DIR_GNL = src/get-next-line
OBJ_DIR = obj
INC_DIR = includes
MLX_DIR = MLX42

# Libft Source Files 
LIBFT_SRCS = $(SRC_DIR_LIBFT)/ft_strchr.c \
             $(SRC_DIR_LIBFT)/ft_strtrim.c \
             $(SRC_DIR_LIBFT)/ft_strncmp.c \
             $(SRC_DIR_LIBFT)/ft_strdup.c \
             $(SRC_DIR_LIBFT)/ft_memset.c \
             $(SRC_DIR_LIBFT)/ft_strlen.c \
             $(SRC_DIR_LIBFT)/ft_strlcpy.c \
             $(SRC_DIR_LIBFT)/ft_split.c \
             $(SRC_DIR_LIBFT)/ft_atoi.c \
             $(SRC_DIR_LIBFT)/ft_memcpy.c \
             $(SRC_DIR_LIBFT)/ft_lst_add_back.c \

# GetNextLine Source Files 
GNL_SRCS = $(SRC_DIR_GNL)/get_next_line.c \
             $(SRC_DIR_GNL)/get_next_line_utils.c \

# Source Files (Core)
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/raycasting.c \
       $(SRC_DIR)/draw.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/hooks.c \
       $(SRC_DIR)/move.c \
       $(SRC_DIR)/parse.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/garbage_collector.c \
       $(SRC_DIR)/utils.1.c \
       $(SRC_DIR)/parce_helper.c \
       $(SRC_DIR)/parce_helper_2.c \
       $(SRC_DIR)/checker_parce.c \
       $(SRC_DIR)/check_parce_2.c \
       $(SRC_DIR)/utils_3.c \

# Object Files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(LIBFT_SRCS:$(SRC_DIR_LIBFT)/%.c=$(OBJ_DIR)/%.o) $(GNL_SRCS:$(SRC_DIR_GNL)/%.c=$(OBJ_DIR)/%.o)


# MLX42 Library
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -L$(MLX_DIR)/build -lmlx42 -L$(HOME)/.brew/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lm
INCLUDES = -I$(MLX_DIR)/include/MLX42 -I$(INC_DIR)

# Dependency Files
DEPS = $(OBJS:.o=.d)

# Rules
all: $(NAME)

# Link the executable
$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

# Compile source files from src/ into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD  -c $< -o $@

# Compile source files from src/libft/ into object files
$(OBJ_DIR)/%.o: $(SRC_DIR_LIBFT)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD  -c $< -o $@

# Compile source files from src/get-next-line/ into object files
$(OBJ_DIR)/%.o: $(SRC_DIR_GNL)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build MLX42
$(MLX_LIB):
	cd $(MLX_DIR) && cmake -B build -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" && cmake --build build -j4

# Clean object files and dependencies
clean:
	rm -rf $(OBJ_DIR)
	cd $(MLX_DIR) && rm -rf build

# Full clean (including executable)
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Include dependency files
-include $(DEPS)