/* parser.c */
#include "../includes/cub3d.h"

int parse_cub_file(char *filename, t_game *data)
{
    int fd;
    char *line;
    int elements_found = 0;
    
    if (!validate_extension(filename))
        return (print_error("Invalid file extension"), 0);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (perror("Error opening file"), 0);
    while ((line = read_line(fd)) && elements_found < 6)
    {
        if (parse_texture(line, &data->tex_paths))
            elements_found++;
        else if (parse_color(line, &data->floor, &data->ceiling))
            elements_found++;
        free(line);
    }
    if (elements_found != 6)
        return (close(fd), print_error("Missing elements"), 0);
    if (!parse_map_section(fd, data))
        return (close(fd), 0);
    close(fd);
    return (validate_map(data));
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

int validate_extension(char *filename)
{
    char *ext;
    int len;
    
    if (!filename)
        return (0);
    len = strlen(filename);
    if (len < 5)
        return (0);
    ext = filename + len - 4;
    return (strcmp(ext, ".cub") == 0);
}

char *read_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int pos = 0;
    static int bytes_read = 0;
    char *line;
    int i = 0;
    
    line = malloc(MAX_LINE);
    if (!line)
        return (NULL);
    while (1)
    {
        if (pos >= bytes_read)
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                break;
            pos = 0;
        }
        if (buffer[pos] == '\n')
        {
            pos++;
            break;
        }
        if (i < MAX_LINE - 1)
            line[i++] = buffer[pos];
        pos++;
    }
    line[i] = '\0';
    return (i == 0 && bytes_read <= 0 ? (free(line), NULL) : line);
}

int	read_map_lines(int fd, char ***temp_map, int *capacity)
{
	char	*line;
	int		count;
	char	**new_map;

	count = 0;
	while ((line = read_line(fd)))
	{
		if (is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (count >= *capacity - 1)
		{
			*capacity *= 2;
			new_map = ft_realloc(*temp_map, sizeof(char *) * (count + 1), 
				sizeof(char *) * (*capacity));
			if (!new_map)
			{
				free(line);
				return (-1);
			}
			*temp_map = new_map;
		}
		(*temp_map)[count++] = line;
	}
	(*temp_map)[count] = NULL;
	return (count);
}
