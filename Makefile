# Project name
NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./minilibx-linux -I./libft
LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

# Directories
SRCDIR = src
INCDIR = includes
OBJDIR = obj
LIBFTDIR = libft

# MinilibX
MLX_URL = https://cdn.intra.42.fr/document/document/25926/minilibx-linux.tgz
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

# Libft
LIBFT_URL = https://github.com/voloshynm/libft
LIBFT_LIB = $(LIBFTDIR)/libft.a

# Source files
SRCFILES = 	main.c \
			init_visuals.c \
			parser.c \
			parse_elements.c \
			parse_elements_helper.c \
			parse_elements_color.c \
			parse_map.c \
			parse_map_directions.c \
			validate_walls.c \
			utils.c \
			utils_2.c \
			raycasting.c \
			raycasting_helper.c \
			raycasting_rays_direction.c \
			controls.c \
			controls_helper.c

# Object files
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))
OBJS = $(addprefix $(OBJDIR)/, $(SRCFILES:.c=.o))

# Headers
HEADERS = $(INCDIR)/cub3d.h

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
YELLOW = \033[0;33m
NC = \033[0m

# Default target
all: $(NAME)

# Download and extract MinilibX only if directory doesn't exist
$(MLX_DIR):
	@echo "$(BLUE)Downloading MinilibX...$(NC)"
	@curl -s $(MLX_URL) -o minilibx-linux.tgz
	@echo "$(BLUE)Extracting MinilibX...$(NC)"
	@tar -xzf minilibx-linux.tgz
	@rm -f minilibx-linux.tgz
	@echo "$(GREEN)MinilibX downloaded and extracted!$(NC)"

# Compile MinilibX only if library doesn't exist
$(MLX_LIB): | $(MLX_DIR)
	@if [ ! -f "$(MLX_LIB)" ]; then \
		echo "$(BLUE)Compiling MinilibX...$(NC)"; \
		$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1; \
		echo "$(GREEN)MinilibX compiled!$(NC)"; \
	else \
		echo "$(GREEN)MinilibX already compiled, skipping...$(NC)"; \
	fi

# Create object directory
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Clone libft repository if it doesn't exist
$(LIBFTDIR):
	@if [ ! -d "$(LIBFTDIR)" ]; then \
		echo "$(BLUE)Cloning libft repository...$(NC)"; \
		git clone $(LIBFT_URL) $(LIBFTDIR); \
		echo "$(GREEN)libft cloned!$(NC)"; \
	else \
		echo "$(GREEN)libft directory already exists, skipping clone...$(NC)"; \
	fi

# Compile libft only if library doesn't exist or sources are newer
$(LIBFT_LIB): | $(LIBFTDIR)
	@if [ ! -f "$(LIBFT_LIB)" ]; then \
		echo "$(BLUE)Compiling libft...$(NC)"; \
		$(MAKE) -C $(LIBFTDIR); \
		echo "$(GREEN)libft compiled!$(NC)"; \
	else \
		echo "$(GREEN)Libft already compiled, skipping...$(NC)"; \
	fi

# Main target - always depend on libft
$(NAME): $(MLX_LIB) $(LIBFT_LIB) $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

# Compile object files - now depends on libft being available
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiled: $<$(NC)"

# Clean object files
clean:
	@if [ -d "$(LIBFTDIR)" ]; then \
		$(MAKE) clean -C $(LIBFTDIR); \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) clean -C $(MLX_DIR) > /dev/null 2>&1; \
	fi
	@rm -rf $(OBJDIR)
	@echo "$(RED)Object files cleaned$(NC)"

# Full clean including MinilibX and libft
fclean: clean
	@if [ -d "$(LIBFTDIR)" ]; then \
		$(MAKE) fclean -C $(LIBFTDIR); \
	fi
	@rm -rf $(MLX_DIR) $(LIBFTDIR)
	@rm -f $(NAME)
	@echo "$(RED)All files cleaned including MinilibX and libft$(NC)"

# Rebuild everything
re: fclean all

# Force recompile MinilibX
remlx:
	@if [ -d "$(MLX_DIR)" ]; then \
		echo "$(BLUE)Force recompiling MinilibX...$(NC)"; \
		$(MAKE) clean -C $(MLX_DIR) > /dev/null 2>&1; \
		$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1; \
		echo "$(GREEN)MinilibX recompiled!$(NC)"; \
	else \
		echo "$(RED)MinilibX directory not found. Run 'make mlx' first.$(NC)"; \
	fi

# Force recompile libft
relibft:
	@if [ -d "$(LIBFTDIR)" ]; then \
		echo "$(BLUE)Force recompiling libft...$(NC)"; \
		$(MAKE) fclean -C $(LIBFTDIR); \
		$(MAKE) -C $(LIBFTDIR); \
		echo "$(GREEN)libft recompiled!$(NC)"; \
	else \
		echo "$(RED)libft directory not found. Run 'make' to clone and compile.$(NC)"; \
	fi

# Setup project structure
setup:
	@mkdir -p $(SRCDIR) $(INCDIR) textures maps
	@echo "$(GREEN)Project structure created!$(NC)"
	@echo "$(BLUE)Directories created: $(SRCDIR)/, $(INCDIR)/, textures/, maps/$(NC)"

# Download MinilibX only
mlx: $(MLX_LIB)

# Show help
help:
	@echo "$(GREEN)Available targets:$(NC)"
	@echo "  $(YELLOW)all$(NC)      - Build the project"
	@echo "  $(YELLOW)clean$(NC)    - Remove object files"
	@echo "  $(YELLOW)fclean$(NC)   - Remove all generated files including MinilibX and libft"
	@echo "  $(YELLOW)re$(NC)       - Rebuild everything"
	@echo "  $(YELLOW)remlx$(NC)    - Force recompile MinilibX only"
	@echo "  $(YELLOW)relibft$(NC)  - Force recompile libft only"
	@echo "  $(YELLOW)setup$(NC)    - Create project directory structure"
	@echo "  $(YELLOW)mlx$(NC)     - Download and compile MinilibX only"
	@echo "  $(YELLOW)help$(NC)     - Show this help"

# Show project status
status:
	@echo "$(BLUE)Project Status:$(NC)"
	@echo "  Name: $(NAME)"
	@echo "  Source files: $(words $(SRCFILES))"
	@echo "  MinilibX: $(if $(wildcard $(MLX_DIR)),$(GREEN)Downloaded$(NC),$(RED)Not downloaded$(NC))"
	@echo "  MinilibX lib: $(if $(wildcard $(MLX_LIB)),$(GREEN)Compiled$(NC),$(RED)Not compiled$(NC))"
	@echo "  libft: $(if $(wildcard $(LIBFTDIR)),$(GREEN)Downloaded$(NC),$(RED)Not downloaded$(NC))"
	@echo "  libft lib: $(if $(wildcard $(LIBFT_LIB)),$(GREEN)Compiled$(NC),$(RED)Not built$(NC))"
	@echo "  Object dir: $(if $(wildcard $(OBJDIR)),$(GREEN)Exists$(NC),$(RED)Missing$(NC))"
	@echo "  Executable: $(if $(wildcard $(NAME)),$(GREEN)Built$(NC),$(RED)Not built$(NC))"

.PHONY: all clean fclean re remlx relibft setup help status mlx
