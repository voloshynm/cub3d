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

int	initialize_game_data(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->floor.r = -1;
	game->ceiling.r = -1;
	game->win_width = WIN_WIDTH;
	game->win_height = WIN_HEIGHT;
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