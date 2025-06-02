/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:00:43 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/02 23:00:44 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_walls(char **map, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (j >= (int)strlen(map[i]))
			{
				if (!check_space_surroundings(map, i, j, height))
					return (0);
			}
			else if (map[i][j] == '0' || is_player_char(map[i][j]))
			{
				if (!check_floor_surroundings(map, i, j, height))
					return (0);
			}
		}
	}
	return (1);
}

int	check_floor_surroundings(char **map, int y, int x, int height)
{
	static int	directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int			i;
	int			new_y;
	int			new_x;

	i = -1;
	while (++i < 4)
	{
		new_y = y + directions[i][0];
		new_x = x + directions[i][1];
		if (new_y < 0 || new_y >= height)
			return (0);
		if (new_x < 0 || new_x >= (int)strlen(map[new_y]))
			return (0);
		if (map[new_y][new_x] == ' ')
			return (0);
	}
	return (1);
}

int	check_space_surroundings(char **map, int y, int x, int height)
{
	static int	directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int			i;
	int			new_y;
	int			new_x;

	i = -1;
	while (++i < 4)
	{
		new_y = y + directions[i][0];
		new_x = x + directions[i][1];
		if (new_y >= 0 && new_y < height && new_x >= 0)
		{
			if (new_x < (int)strlen(map[new_y]))
			{
				if (map[new_y][new_x] != '1' && map[new_y][new_x] != ' ')
					return (0);
			}
		}
	}
	return (1);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
