/* parse_elements.c */
#include "../includes/cub3d.h"

int	parse_north_texture(char *trimmed, t_texture *textures)
{
	char	*path;

	if (ft_strncmp(trimmed, "NO ", 3) == 0 && !textures->north)
	{
		path = extract_path(trimmed + 3);
		textures->north = path;
		return (path != NULL);
	}
	return (0);
}

int	parse_south_texture(char *trimmed, t_texture *textures)
{
	char	*path;

	if (ft_strncmp(trimmed, "SO ", 3) == 0 && !textures->south)
	{
		path = extract_path(trimmed + 3);
		textures->south = path;
		return (path != NULL);
	}
	return (0);
}

int	parse_east_texture(char *trimmed, t_texture *textures)
{
	char	*path;

	if (ft_strncmp(trimmed, "EA ", 3) == 0 && !textures->east)
	{
		path = extract_path(trimmed + 3);
		textures->east = path;
		return (path != NULL);
	}
	return (0);
}

int	parse_west_texture(char *trimmed, t_texture *textures)
{
	char	*path;

	if (ft_strncmp(trimmed, "WE ", 3) == 0 && !textures->west)
	{
		path = extract_path(trimmed + 3);
		textures->west = path;
		return (path != NULL);
	}
	return (0);
}

char	*skip_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}