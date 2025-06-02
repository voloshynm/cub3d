/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:00:19 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/03 00:39:24 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_cub_file(char *filename, t_game *data)
{
	int		fd;
	char	*line;
	int		elements_found;

	elements_found = 0;
	if (!validate_extension(filename))
		return (print_error("Invalid file extension"), 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), 0);
	while (elements_found < 6)
	{
		line = read_line(fd);
		if (!line)
			return (close(fd), print_error("Unexpected end of file"), 0);
		if (parse_texture(line, &data->tex_paths)
			|| parse_color(line, &data->floor, &data->ceiling))
			elements_found++;
		free(line);
	}
	if (elements_found != 6)
		return (close(fd), print_error("Missing elements"), 0);
	if (!parse_map_section(fd, data))
		return (close(fd), 0);
	return (close(fd), validate_map(data));
}

int	validate_map(t_game *data)
{
	if (!find_player(data))
		return (print_error("Player not found"), 0);
	if (!check_valid_characters(data))
		return (print_error("Invalid characters"), 0);
	if (!check_walls(data->map, data->map_height, data->map_width))
		return (print_error("Map not enclosed"), 0);
	return (1);
}

int	validate_extension(char *filename)
{
	char	*ext;
	int		len;

	if (!filename)
		return (0);
	len = strlen(filename);
	if (len < 5)
		return (0);
	ext = filename + len - 4;
	return (strcmp(ext, ".cub") == 0);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	read_map_lines(int fd, char ***temp_map, int *capacity, int count)
{
	char	*line;
	char	**new_map;

	while (1)
	{
		line = read_line(fd);
		if (!line)
			break ;
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (count >= *capacity - 1)
		{
			*capacity *= 2;
			new_map = ft_realloc(*temp_map, sizeof(char *) * (count + 1),
					sizeof(char *) * (*capacity));
			if (!new_map)
				return (free(line), -1);
			*temp_map = new_map;
		}
		(*temp_map)[count++] = line;
	}
	return ((*temp_map)[count] = NULL, count);
}
