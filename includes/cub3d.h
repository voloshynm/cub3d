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

/* ============ STRUCTURES ============ */
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

/* ============ INITIALIZATION & SETUP ============ */
int		initialize_game_data(t_game *game);
int		init_game(t_game *game);
int		init_mlx_components(t_game *game);
int		init_screen_image(t_game *game);
int		load_textures(t_game *game);
int		load_single_texture(t_game *game, char *path, int index);
void	init_player(t_game *game);

/* ============ PARSING FUNCTIONS ============ */
int		parse_cub_file(char *filename, t_game *game);
int		validate_extension(char *filename);
char	*read_line(int fd);

/* Texture parsing */
int		parse_texture(char *line, t_texture *textures);
int		parse_north_texture(char *trimmed, t_texture *textures);
int		parse_south_texture(char *trimmed, t_texture *textures);
int		parse_east_texture(char *trimmed, t_texture *textures);
int		parse_west_texture(char *trimmed, t_texture *textures);
char	*extract_path(char *str);

/* Color parsing */
int		parse_color(char *line, t_color *floor, t_color *ceiling);
int		extract_rgb(char *str, t_color *color);
char	*find_next_value(char *ptr, int index);
void	set_color_values(t_color *color, int *values);

/* Map parsing */
int		parse_map_section(int fd, t_game *game);
int		read_map_lines(int fd, char ***temp_map, int *capacity);
int		expand_map_if_needed(char ***temp_map, int *capacity, int count);
void	calculate_map_width(t_game *game);

/* ============ MAP VALIDATION ============ */
int		validate_map(t_game *game);
int		check_walls(char **map, int height, int width);
int		check_valid_characters(t_game *game);
int		check_floor_surroundings(char **map, int y, int x, int height);
int		check_space_surroundings(char **map, int y, int x, int height);
int		find_player(t_game *game);
int		is_player_char(char c);
int		is_valid_map_char(char c);

/* ============ PLAYER SETUP ============ */
void	set_player_position(t_game *data, int i, int j, char dir);
void	set_player_direction(t_game *data, char dir);
void	set_north_direction(t_game *data);
void	set_south_direction(t_game *data);
void	set_east_direction(t_game *data);
void	set_west_direction(t_game *data);

/* ============ GAME LOOP & RENDERING ============ */
int		game_loop(t_game *game);
int		render_frame(t_game *game);
void	draw_background(t_game *game);
void	cast_rays(t_game *game);

/* ============ RAYCASTING ============ */
void	init_ray(t_ray *ray, t_game *game, int x);
void	init_ray_direction(t_ray *ray, t_game *game);
void	init_x_direction(t_ray *ray, t_game *game);
void	init_y_direction(t_ray *ray, t_game *game);
void	calculate_delta_distances(t_ray *ray);
void	perform_dda(t_ray *ray, char **map);
void	calculate_wall_distance(t_ray *ray, t_game *game);
void	calculate_draw_limits(t_ray *ray, t_game *game);

/* ============ TEXTURE RENDERING ============ */
void	draw_vertical_line(t_game *game, int x, t_ray *ray);
double	calculate_wall_x(t_ray *ray, t_game *game);
int		calculate_tex_x(t_ray *ray, double wall_x);
void	draw_textured_pixel(t_game *game, int x, int y, t_ray *ray,
			double *tex_pos, double step, int tex_x);
int		get_texture_color(t_game *game, t_ray *ray, int y, int tex_x);
int		determine_texture_number(t_ray *ray);

/* ============ CONTROLS & INPUT ============ */
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(t_game *game);

/* Movement functions */
void	handle_forward_movement(t_game *game);
void	handle_backward_movement(t_game *game);
void	handle_left_strafe(t_game *game);
void	handle_right_strafe(t_game *game);
void	move_player(t_game *game, double move_x, double move_y);
int		is_valid_position(t_game *game, double x, double y);

/* Rotation functions */
void	rotate_player(t_game *game, double rot_speed);
void	rotate_direction_vector(t_game *game, double rot_speed, double old_dir_x);
void	rotate_camera_plane(t_game *game, double rot_speed, double old_plane_x);

/* ============ UTILITY FUNCTIONS ============ */
/* String utilities */
char	*skip_whitespace(char *str);
char	*find_path_end(char *start);
char	*trim_whitespace(char *str);
int		is_empty_line(char *line);
char	*ft_strncpy(char *dest, const char *src, size_t n);

/* Memory utilities */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	free_game_data(t_game *game);
void	cleanup_and_exit(t_game *game, int exit_code);

/* Graphics utilities */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		create_rgb(int r, int g, int b);

/* Error handling */
void	print_error(char *message);

#endif