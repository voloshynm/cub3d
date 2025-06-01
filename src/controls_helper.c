/* controls.c */
#include "../includes/cub3d.h"

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

int	is_valid_position(t_game *game, double x, double y)
{
	return (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height);
}
