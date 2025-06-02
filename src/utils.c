/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:00:38 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/02 23:46:57 by mvoloshy         ###   ########.fr       */
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

void	print_error(char *message)
{
	printf("Error\n%s\n", message);
}

static int	get_next_char(int fd, char *c)
{
	static char	buffer[BUFFER_SIZE];
	static int	pos = 0;
	static int	bytes_read = 0;

	if (pos >= bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (0);
		pos = 0;
	}
	*c = buffer[pos++];
	return (1);
}

char	*read_line(int fd)
{
	char	*line;
	int		i;
	char	ch;

	ch = 0;
	i = 0;
	line = malloc(MAX_LINE);
	if (!line)
		return (NULL);
	while (i < MAX_LINE - 1)
	{
		if (!get_next_char(fd, &ch))
			break ;
		if (ch == '\n')
			break ;
		line[i++] = ch;
	}
	line[i] = '\0';
	if (i == 0 && ch != '\n')
		return (free(line), NULL);
	return (line);
}
