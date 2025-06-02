/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:58:53 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/02 22:59:10 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	close_window(t_game *game)
{
	cleanup_and_exit(game, 0);
	return (0);
}
