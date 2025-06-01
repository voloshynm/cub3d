/* raycasting.c */
#include "../includes/cub3d.h"

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
