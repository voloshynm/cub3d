/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visuals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:59:34 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/03 00:22:23 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
