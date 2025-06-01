/* parse_map.c */
#include "../includes/cub3d.h"

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
