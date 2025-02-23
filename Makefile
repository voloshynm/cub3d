SRC = src/main.c src/game_utils.c src/raycaster.c src/player_controls.c src/map_utils.c

NAME = game

OBJDIR = obj
OBJDIR_bonus = obj_bonus
OBJS = $(SRC:src/%.c=$(OBJDIR)/%.o)
OBJS_bonus = $(SRC_bonus:src/%.c=$(OBJDIR_bonus)/%.o)

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -I./minilibx -I./libft -I./inc
LDFLAGS = -L./minilibx -lmlx -L./libft -lft -lm -lXext -lX11

all: minilibx/libmlx.a libft/libft.a $(NAME)

bonus: minilibx/libmlx.a libft/libft.a $(NAME_bonus)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(NAME_bonus): $(OBJS_bonus)
	$(CC) $(CFLAGS) -o $(NAME_bonus) $(OBJS_bonus) $(LDFLAGS)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_bonus)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

minilibx/libmlx.a: minilibx
	$(MAKE) -C minilibx

minilibx:
	curl -LOJ https://cdn.intra.42.fr/document/document/26474/minilibx-linux.tgz
	tar -xzf minilibx-linux.tgz
	mv minilibx-linux minilibx
	rm -r minilibx-linux.tgz

libft/libft.a:
	git clone git@github.com:Harley-Davidson/libft.git libft
	$(MAKE) -C libft

clean:
	rm -f $(OBJS) $(OBJS_bonus)
	$(MAKE) -C libft clean
	if [ -d minilibx ]; then $(MAKE) -C minilibx clean; fi

fclean: clean
	rm -f $(NAME) $(NAME_bonus)
	$(MAKE) -C libft fclean
	rm -rf minilibx minilibx-linux.tgz libft $(OBJDIR) $(OBJDIR_bonus)

re: fclean all

.PHONY: all clean fclean re bonus

