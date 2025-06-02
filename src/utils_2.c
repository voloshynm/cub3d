/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <mvoloshy@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:00:34 by mvoloshy          #+#    #+#             */
/*   Updated: 2025/06/02 23:00:35 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cleanup_and_exit(t_game *game, int exit_code)
{
	int	i;

	i = 0;
	if (game->mlx)
	{
		while (i < 4)
		{
			if (game->textures[i].img)
				mlx_destroy_image(game->mlx, game->textures[i].img);
			i++;
		}
		if (game->screen.img)
			mlx_destroy_image(game->mlx, game->screen.img);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_game_data(game);
	exit(exit_code);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
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
