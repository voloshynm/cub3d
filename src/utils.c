/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:00:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/02 23:00:39 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->line_length
				+ x * (img->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

char	*trim_whitespace(char *str)
{
	char	*start;
	char	*end;

	if (!str)
		return (NULL);
	start = str;
	while (*start == ' ' || *start == '\t')
		start++;
	if (*start == '\0')
		return (NULL);
	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = '\0';
	return (start);
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

void	free_game_data(t_game *game)
{
	int	i;

	i = 0;
	if (game->tex_paths.north)
		free(game->tex_paths.north);
	if (game->tex_paths.south)
		free(game->tex_paths.south);
	if (game->tex_paths.east)
		free(game->tex_paths.east);
	if (game->tex_paths.west)
		free(game->tex_paths.west);
	if (game->map)
	{
		while (i < game->map_height)
			free(game->map[i++]);
		free(game->map);
	}
}

void	print_error(char *message)
{
	printf("Error\n%s\n", message);
}
