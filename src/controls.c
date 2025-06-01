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
