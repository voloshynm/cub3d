/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:59:56 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/02 22:59:57 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_texture(char *line, t_texture *textures)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	if (parse_north_texture(trimmed, textures))
		return (1);
	if (parse_south_texture(trimmed, textures))
		return (1);
	if (parse_east_texture(trimmed, textures))
		return (1);
	if (parse_west_texture(trimmed, textures))
		return (1);
	return (0);
}

char	*extract_path(char *str)
{
	char	*start;
	char	*end;
	char	*path;
	int		len;

	start = skip_whitespace(str);
	if (*start == '\0')
		return (NULL);
	end = find_path_end(start);
	len = end - start;
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, start, len);
	path[len] = '\0';
	return (path);
}

char	*find_path_end(char *start)
{
	char	*end;

	end = start;
	while (*end && *end != ' ' && *end != '\t' && *end != '\n')
		end++;
	return (end);
}

char	*find_next_value(char *ptr, int index)
{
	while (*ptr && *ptr != ',')
		ptr++;
	if (index < 2 && *ptr != ',')
		return (NULL);
	if (*ptr == ',')
		ptr++;
	return (ptr);
}
