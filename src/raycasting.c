/* raycasting.c */
#include "../includes/cub3d.h"

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
