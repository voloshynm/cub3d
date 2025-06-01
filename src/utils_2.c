/* utils.c */
#include "../includes/cub3d.h"

void cleanup_and_exit(t_game *game, int exit_code)
{
    int i = 0;
    
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

void print_error(char *message)
{
    printf("Error\n%s\n", message);
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