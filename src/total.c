/* cub3d.h */
#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include "mlx.h"
# include "../libft/libft.h"

/* Buffer and window constants */
# define BUFFER_SIZE 1024
# define MAX_LINE 2048
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

/* Movement and rotation speeds */
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* Key codes for Linux */
# define KEY_W 119
# define KEY_A 100
# define KEY_S 115
# define KEY_D 97
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* Texture indices */
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

/* Structures remain the same */
typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		textures[4];
	t_texture	tex_paths;
	t_color		floor;
	t_color		ceiling;
	char		**map;
	int			map_height;
	int			map_width;
	int			win_width;
	int			win_height;
	t_player	player;
}	t_game;

int		initialize_game_data(t_game *game);
int		init_mlx_components(t_game *game);
int		init_screen_image(t_game *game);
int		load_single_texture(t_game *game, char *path, int index);
void	handle_forward_movement(t_game *game);
void	handle_backward_movement(t_game *game);
void	handle_left_strafe(t_game *game);
void	handle_right_strafe(t_game *game);
int		is_valid_position(t_game *game, double x, double y);
void	rotate_direction_vector(t_game *game, double rot_speed, double old_dir_x);
void	rotate_camera_plane(t_game *game, double rot_speed, double old_plane_x);
int		parse_north_texture(char *trimmed, t_texture *textures);
int		parse_south_texture(char *trimmed, t_texture *textures);
int		parse_east_texture(char *trimmed, t_texture *textures);
int		parse_west_texture(char *trimmed, t_texture *textures);
char	*skip_whitespace(char *str);
char	*find_path_end(char *start);
char	*find_next_value(char *ptr, int index);
void	set_color_values(t_color *color, int *values);
int		read_map_lines(int fd, char **temp_map, int *capacity);
int		expand_map_if_needed(char ***temp_map, int *capacity, int count);
void	set_player_position(t_game *data, int i, int j, char dir);
void	set_player_direction(t_game *data, char dir);
void	set_north_direction(t_game *data);
void	set_south_direction(t_game *data);
void	set_east_direction(t_game *data);
void	set_west_direction(t_game *data);
int		is_valid_map_char(char c);
void	draw_background(t_game *game);
void	init_ray(t_ray *ray, t_game *game, int x);
void	calculate_delta_distances(t_ray *ray);
void	init_x_direction(t_ray *ray, t_game *game);
void	init_y_direction(t_ray *ray, t_game *game);
void	calculate_draw_limits(t_ray *ray, t_game *game);
double	calculate_wall_x(t_ray *ray, t_game *game);
int		calculate_tex_x(t_ray *ray, double wall_x);
void	draw_textured_pixel(t_game *game, int x, int y, t_ray *ray,
			double *tex_pos, double step, int tex_x);
int		determine_texture_number(t_ray *ray);

int		parse_cub_file(char *filename, t_game *game);
int		validate_extension(char *filename);
char	*read_line(int fd);
int		parse_texture(char *line, t_texture *textures);
int		parse_color(char *line, t_color *floor, t_color *ceiling);
char	*extract_path(char *str);
int		extract_rgb(char *str, t_color *color);
int		parse_map_section(int fd, t_game *game);
int		validate_map(t_game *game);
int		check_walls(char **map, int height, int width);
int		find_player(t_game *game);
void	calculate_map_width(t_game *game);
int		check_valid_characters(t_game *game);
int		check_floor_surroundings(char **map, int y, int x, int height);
int		check_space_surroundings(char **map, int y, int x, int height);
int		is_player_char(char c);
int		init_game(t_game *game);
int		load_textures(t_game *game);
void	init_player(t_game *game);
int		game_loop(t_game *game);
int		render_frame(t_game *game);
void	cast_rays(t_game *game);
void	init_ray_direction(t_ray *ray, t_game *game);
void	perform_dda(t_ray *ray, char **map);
void	calculate_wall_distance(t_ray *ray, t_game *game);
void	draw_vertical_line(t_game *game, int x, t_ray *ray);
int		get_texture_color(t_game *game, t_ray *ray, int y, int tex_x);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(t_game *game);
void	move_player(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, double rot_speed);
char	*trim_whitespace(char *str);
int		is_empty_line(char *line);
void	print_error(char *message);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		create_rgb(int r, int g, int b);
void	free_game_data(t_game *game);
void	cleanup_and_exit(t_game *game, int exit_code);
char	*ft_strncpy(char *dest, const char *src, size_t n);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif
/* controls.c */
#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		handle_forward_movement(game);
	else if (keycode == KEY_S)
		handle_backward_movement(game);
	else if (keycode == KEY_A)
		handle_left_strafe(game);
	else if (keycode == KEY_D)
		handle_right_strafe(game);
	else if (keycode == KEY_LEFT)
		rotate_player(game, -ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, ROT_SPEED);
	return (0);
}

void	handle_forward_movement(t_game *game)
{
	move_player(game, game->player.dir_x * MOVE_SPEED,
		game->player.dir_y * MOVE_SPEED);
}

void	handle_backward_movement(t_game *game)
{
	move_player(game, -game->player.dir_x * MOVE_SPEED,
		-game->player.dir_y * MOVE_SPEED);
}

void	handle_left_strafe(t_game *game)
{
	move_player(game, -game->player.dir_y * MOVE_SPEED,
		game->player.dir_x * MOVE_SPEED);
}

void	handle_right_strafe(t_game *game)
{
	move_player(game, game->player.dir_y * MOVE_SPEED,
		-game->player.dir_x * MOVE_SPEED);
}

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	if (!is_valid_position(game, new_x, new_y))
		return ;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
}

int	is_valid_position(t_game *game, double x, double y)
{
	return (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height);
}

void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	rotate_direction_vector(game, rot_speed, old_dir_x);
	rotate_camera_plane(game, rot_speed, old_plane_x);
}

void	rotate_direction_vector(t_game *game, double rot_speed, double old_dir_x)
{
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
}

void	rotate_camera_plane(t_game *game, double rot_speed, double old_plane_x)
{
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

int	close_window(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}
/* main.c */
#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!initialize_game_data(&game))
		return (1);
	if (!parse_cub_file(argv[1], &game) || !init_game(&game))
	{
		free_game_data(&game);
		return (1);
	}
	game_loop(&game);
	cleanup_and_exit(&game, 0);
	return (0);
}

int	initialize_game_data(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->floor.r = -1;
	game->ceiling.r = -1;
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
	return (1);
}

int	init_game(t_game *game)
{
	if (!init_mlx_components(game))
		return (0);
	if (!init_screen_image(game))
		return (0);
	if (!load_textures(game))
		return (0);
	return (1);
}

int	init_mlx_components(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error("MLX initialization failed"), 0);
	game->win = mlx_new_window(game->mlx, game->win_width,
			game->win_height, "cub3D");
	if (!game->win)
		return (print_error("Window creation failed"), 0);
	return (1);
}

int	init_screen_image(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, game->win_width,
			game->win_height);
	if (!game->screen.img)
		return (print_error("Image creation failed"), 0);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel, &game->screen.line_length,
			&game->screen.endian);
	game->screen.width = game->win_width;
	game->screen.height = game->win_height;
	return (1);
}

int	load_textures(t_game *game)
{
	char	*paths[4];
	int		i;

	paths[0] = game->tex_paths.north;
	paths[1] = game->tex_paths.south;
	paths[2] = game->tex_paths.east;
	paths[3] = game->tex_paths.west;
	i = -1;
	while (++i < 4)
	{
		if (!load_single_texture(game, paths[i], i))
			return (0);
	}
	return (1);
}

int	load_single_texture(t_game *game, char *path, int index)
{
	game->textures[index].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[index].width, &game->textures[index].height);
	if (!game->textures[index].img)
		return (print_error("Texture loading failed"), 0);
	game->textures[index].addr = mlx_get_data_addr(game->textures[index].img,
			&game->textures[index].bits_per_pixel,
			&game->textures[index].line_length,
			&game->textures[index].endian);
	return (1);
}
/* parse_elements.c */
#include "../includes/cub3d.h"

int	parse_texture(char *line, t_texture *textures)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	if (parse_north_texture(trimmed, textures))
		return (1);
	if (parse_south_texture(trimmed, textures))
		return (1);
	if (parse_east_texture(trimmed, textures))
		return (1);
	if (parse_west_texture(trimmed, textures))
		return (1);
	return (0);
}

int	parse_north_texture(char *trimmed, t_texture *textures)
{
	char	*path;

	if (ft_strncmp(trimmed, "NO ", 3) == 0 && !textures->north)
	{
		path = extract_path(trimmed + 3);
		textures->north = path;
		return (path != NULL);
	}
	return (0);
}

int	parse_south_texture(char *trimmed, t_texture *textures)
{
	char	*path;

	if (ft_strncmp(trimmed, "SO ", 3) == 0 && !textures->south)
	{
		path = extract_path(trimmed + 3);
		textures->south = path;
		return (path != NULL);
	}
	return (0);
}

int	parse_east_texture(char *trimmed, t_texture *textures)
{
	char	*path;

	if (ft_strncmp(trimmed, "EA ", 3) == 0 && !textures->east)
	{
		path = extract_path(trimmed + 3);
		textures->east = path;
		return (path != NULL);
	}
	return (0);
}

int	parse_west_texture(char *trimmed, t_texture *textures)
{
	char	*path;

	if (ft_strncmp(trimmed, "WE ", 3) == 0 && !textures->west)
	{
		path = extract_path(trimmed + 3);
		textures->west = path;
		return (path != NULL);
	}
	return (0);
}

char	*extract_path(char *str)
{
	char	*start;
	char	*end;
	char	*path;
	int		len;

	start = skip_whitespace(str);
	if (*start == '\0')
		return (NULL);
	end = find_path_end(start);
	len = end - start;
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, start, len);
	path[len] = '\0';
	return (path);
}

char	*skip_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

char	*find_path_end(char *start)
{
	char	*end;

	end = start;
	while (*end && *end != ' ' && *end != '\t' && *end != '\n')
		end++;
	return (end);
}

int	parse_color(char *line, t_color *floor, t_color *ceiling)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "F ", 2) == 0 && floor->r == -1)
		return (extract_rgb(trimmed + 2, floor));
	if (ft_strncmp(trimmed, "C ", 2) == 0 && ceiling->r == -1)
		return (extract_rgb(trimmed + 2, ceiling));
	return (0);
}

int	extract_rgb(char *str, t_color *color)
{
	char	*ptr;
	int		values[3];
	int		i;

	ptr = skip_whitespace(str);
	i = 0;
	while (i < 3)
	{
		values[i] = ft_atoi(ptr);
		if (values[i] < 0 || values[i] > 255)
			return (0);
		ptr = find_next_value(ptr, i);
		if (!ptr && i < 2)
			return (0);
		i++;
	}
	set_color_values(color, values);
	return (1);
}

char	*find_next_value(char *ptr, int index)
{
	while (*ptr && *ptr != ',')
		ptr++;
	if (index < 2 && *ptr != ',')
		return (NULL);
	if (*ptr == ',')
		ptr++;
	return (ptr);
}

void	set_color_values(t_color *color, int *values)
{
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
}
/* parse_map.c */
#include "../includes/cub3d.h"

int	read_map_lines(int fd, char **temp_map, int *capacity)
{
	char	*line;
	int		count;
	char	**new_map;

	count = 0;
	while ((line = read_line(fd)))
	{
		if (is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (count >= *capacity - 1)
		{
			*capacity *= 2;
			new_map = ft_realloc(temp_map, sizeof(char *) * (count + 1), 
				sizeof(char *) * (*capacity));
			if (!new_map)
			{
				free(line);
				return (-1);
			}
			temp_map = new_map;
		}
		temp_map[count++] = line;
	}
	temp_map[count] = NULL;
	return (count);
}

int	parse_map_section(int fd, t_game *data)
{
	char	**temp_map;
	int		capacity;
	int		count;

	capacity = 10;
	temp_map = malloc(sizeof(char *) * capacity);
	if (!temp_map)
		return (0);
	count = read_map_lines(fd, temp_map, &capacity);
	if (count <= 0)
	{
		free(temp_map);
		return (0);
	}
	data->map = temp_map;
	data->map_height = count;
	calculate_map_width(data);
	return (1);
}

void	calculate_map_width(t_game *data)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (i < data->map_height)
	{
		current_width = ft_strlen(data->map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	data->map_width = max_width;
}

int	validate_map(t_game *data)
{
	if (!find_player(data))
		return (print_error("Player not found"), 0);
	if (!check_valid_characters(data))
		return (print_error("Invalid characters"), 0);
	if (!check_walls(data->map, data->map_height, data->map_width))
		return (print_error("Map not enclosed"), 0);
	return (1);
}

int	find_player(t_game *data)
{
	int		i;
	int		j;
	int		player_count;
	char	player_dir;

	i = 0;
	player_count = 0;
	player_dir = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
				data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				set_player_position(data, i, j, data->map[i][j]);
				player_dir = data->map[i][j];
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count == 1)
		set_player_direction(data, player_dir);
	return (player_count == 1);
}

void	set_player_position(t_game *data, int i, int j, char dir)
{
	data->player.x = j + 0.5;
	data->player.y = i + 0.5;
	(void)dir;  // This suppresses the unused parameter warning
}

void	set_player_direction(t_game *data, char dir)
{
	if (dir == 'N')
		set_north_direction(data);
	else if (dir == 'S')
		set_south_direction(data);
	else if (dir == 'E')
		set_east_direction(data);
	else if (dir == 'W')
		set_west_direction(data);
}

void	set_north_direction(t_game *data)
{
	data->player.dir_x = 0;
	data->player.dir_y = -1;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0;
}

void	set_south_direction(t_game *data)
{
	data->player.dir_x = 0;
	data->player.dir_y = 1;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0;
}

void	set_east_direction(t_game *data)
{
	data->player.dir_x = 1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
}

void	set_west_direction(t_game *data)
{
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = -0.66;
}

int	check_valid_characters(t_game *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (data->map[i][j])
		{
			c = data->map[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' &&
				c != 'E' && c != 'W' && c != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
/* raycasting.c */
#include "../includes/cub3d.h"

int	game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
	return (1);
}

int	render_frame(t_game *game)
{
	draw_background(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->win_width)
	{
		y = 0;
		while (y < game->win_height / 2)
		{
			my_mlx_pixel_put(&game->screen, x, y,
				create_rgb(game->ceiling.r, game->ceiling.g, game->ceiling.b));
			y++;
		}
		while (y < game->win_height)
		{
			my_mlx_pixel_put(&game->screen, x, y,
				create_rgb(game->floor.r, game->floor.g, game->floor.b));
			y++;
		}
		x++;
	}
}

void	cast_rays(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < game->win_width)
	{
		init_ray(&ray, game, x);
		init_ray_direction(&ray, game);
		perform_dda(&ray, game->map);
		calculate_wall_distance(&ray, game);
		draw_vertical_line(game, x, &ray);
		x++;
	}
}

void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)game->win_width - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	calculate_delta_distances(ray);
	ray->hit = 0;
}

void	calculate_delta_distances(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	init_ray_direction(t_ray *ray, t_game *game)
{
	init_x_direction(ray, game);
	init_y_direction(ray, game);
}

void	init_x_direction(t_ray *ray, t_game *game)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
}

void	init_y_direction(t_ray *ray, t_game *game)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, char **map)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(game->win_height / ray->perp_wall_dist);
	calculate_draw_limits(ray, game);
}

void	calculate_draw_limits(t_ray *ray, t_game *game)
{
	ray->draw_start = -ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
}

void	draw_vertical_line(t_game *game, int x, t_ray *ray)
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;

	wall_x = calculate_wall_x(ray, game);
	tex_x = calculate_tex_x(ray, wall_x);
	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - game->win_height / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		draw_textured_pixel(game, x, y, ray, &tex_pos, step, tex_x);
		y++;
	}
}

double	calculate_wall_x(t_ray *ray, t_game *game)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	calculate_tex_x(t_ray *ray, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

void	draw_textured_pixel(t_game *game, int x, int y, t_ray *ray,
		double *tex_pos, double step, int tex_x)
{
	int	tex_y;
	int	color;

	tex_y = (int)*tex_pos & (TEX_HEIGHT - 1);
	*tex_pos += step;
	color = get_texture_color(game, ray, tex_y, tex_x);
	my_mlx_pixel_put(&game->screen, x, y, color);
}

int	get_texture_color(t_game *game, t_ray *ray, int tex_y, int tex_x)
{
	int	tex_num;
	int	color;

	tex_num = determine_texture_number(ray);
	color = *(int *)(game->textures[tex_num].addr
			+ (tex_y * game->textures[tex_num].line_length
				+ tex_x * (game->textures[tex_num].bits_per_pixel / 8)));
	if (ray->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

int	determine_texture_number(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}
/* parser.c */
#include "../includes/cub3d.h"

int parse_cub_file(char *filename, t_game *data)
{
    int fd;
    char *line;
    int elements_found = 0;
    
    if (!validate_extension(filename))
        return (print_error("Invalid file extension"), 0);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (perror("Error opening file"), 0);
    while ((line = read_line(fd)) && elements_found < 6)
    {
        if (parse_texture(line, &data->tex_paths))
            elements_found++;
        else if (parse_color(line, &data->floor, &data->ceiling))
            elements_found++;
        free(line);
    }
    if (elements_found != 6)
        return (close(fd), print_error("Missing elements"), 0);
    if (!parse_map_section(fd, data))
        return (close(fd), 0);
    close(fd);
    return (validate_map(data));
}

int validate_extension(char *filename)
{
    char *ext;
    int len;
    
    if (!filename)
        return (0);
    len = strlen(filename);
    if (len < 5)
        return (0);
    ext = filename + len - 4;
    return (strcmp(ext, ".cub") == 0);
}

char *read_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int pos = 0;
    static int bytes_read = 0;
    char *line;
    int i = 0;
    
    line = malloc(MAX_LINE);
    if (!line)
        return (NULL);
    while (1)
    {
        if (pos >= bytes_read)
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;
            pos = 0;
        }
        if (buffer[pos] == '\n')
        {
            pos++;
            break;
        }
        if (i < MAX_LINE - 1)
            line[i++] = buffer[pos];
        pos++;
    }
    line[i] = '\0';
    return (i == 0 && bytes_read <= 0 ? (free(line), NULL) : line);
}
/* utils.c */
#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    
    if (x >= 0 && x < img->width && y >= 0 && y < img->height)
    {
        dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

char *trim_whitespace(char *str)
{
    char *start;
    char *end;
    
    if (!str)
        return (NULL);
    start = str;
    while (*start == ' ' || *start == '\t')
        start++;
    if (*start == '\0')
        return (NULL);
    end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
        end--;
    *(end + 1) = '\0';
    return (start);
}

int is_empty_line(char *line)
{
    int i = 0;
    
    if (!line)
        return (1);
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

void free_game_data(t_game *game)
{
    int i = 0;
    
    if (game->tex_paths.north)
        free(game->tex_paths.north);
    if (game->tex_paths.south)
        free(game->tex_paths.south);
    if (game->tex_paths.east)
        free(game->tex_paths.east);
    if (game->tex_paths.west)
        free(game->tex_paths.west);
    if (game->map)
    {
        while (i < game->map_height)
            free(game->map[i++]);
        free(game->map);
    }
}

void cleanup_and_exit(t_game *game, int exit_code)
{
    int i = 0;
    
    if (game->mlx)
    {
        while (i < 4)
        {
            if (game->textures[i].img)
                mlx_destroy_image(game->mlx, game->textures[i].img);
            i++;
        }
        if (game->screen.img)
            mlx_destroy_image(game->mlx, game->screen.img);
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    free_game_data(game);
    exit(exit_code);
}

void print_error(char *message)
{
    printf("Error\n%s\n", message);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
/* validate_walls.c */
#include "../includes/cub3d.h"

int check_walls(char **map, int height, int width)
{
    int i = 0;
    int j;
    
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (j >= (int)strlen(map[i]))  // Cast strlen to int
            {
                if (!check_space_surroundings(map, i, j, height))
                    return (0);
            }
            else if (map[i][j] == '0' || is_player_char(map[i][j]))
            {
                if (!check_floor_surroundings(map, i, j, height))
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int check_floor_surroundings(char **map, int y, int x, int height)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int i = 0;
    int new_y, new_x;
    
    while (i < 4)
    {
        new_y = y + directions[i][0];
        new_x = x + directions[i][1];
        if (new_y < 0 || new_y >= height)
            return (0);
        if (new_x < 0 || new_x >= (int)strlen(map[new_y]))  // Cast strlen to int
            return (0);
        if (map[new_y][new_x] == ' ')
            return (0);
        i++;
    }
    return (1);
}

int check_space_surroundings(char **map, int y, int x, int height)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int i = 0;
    int new_y, new_x;
    
    while (i < 4)
    {
        new_y = y + directions[i][0];
        new_x = x + directions[i][1];
        if (new_y >= 0 && new_y < height && new_x >= 0)
        {
            if (new_x < (int)strlen(map[new_y]))  // Cast strlen to int
            {
                if (map[new_y][new_x] != '1' && map[new_y][new_x] != ' ')
                    return (0);
            }
        }
        i++;
    }
    return (1);
}

int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
