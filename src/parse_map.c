/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:00:05 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/02 23:00:07 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_map_section(int fd, t_game *data)
{
	char	**temp_map;
	int		capacity;
	int		count;

	count = 0;
	capacity = 10;
	temp_map = malloc(sizeof(char *) * capacity);
	if (!temp_map)
		return (0);
	count = read_map_lines(fd, &temp_map, &capacity, count);
	if (count <= 0)
	{
		free(temp_map);
		return (0);
	}
	data->map = temp_map;
	data->map_height = count;
	calculate_map_width(data);
	return (1);
}

void	calculate_map_width(t_game *data)
{
	int	i;
	int	max_width;
	int	current_width;

	if (!data || !data->map)
		return ;
	i = 0;
	max_width = 0;
	while (i < data->map_height)
	{
		if (data->map[i])
		{
			current_width = ft_strlen(data->map[i]);
			if (current_width > max_width)
				max_width = current_width;
		}
		i++;
	}
	data->map_width = max_width;
}

int	find_player(t_game *data)
{
	int		i;
	int		j;
	int		player_count;
	char	player_dir;

	i = -1;
	player_count = 0;
	player_dir = 0;
	while (++i < data->map_height)
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
				data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				set_player_position(data, i, j, data->map[i][j]);
				player_dir = data->map[i][j];
				player_count++;
			}
		}
	}
	if (player_count == 1)
		set_player_direction(data, player_dir);
	return (player_count == 1);
}

void	set_player_position(t_game *data, int i, int j, char dir)
{
	data->player.x = j + 0.5;
	data->player.y = i + 0.5;
	(void)dir;
}

int	check_valid_characters(t_game *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (data->map[i][j])
		{
			c = data->map[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
