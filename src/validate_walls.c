/* validate_walls.c */
#include "../includes/cub3d.h"

int check_walls(char **map, int height, int width)
{
    int i = 0;
    int j;
    
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            if (j >= (int)strlen(map[i]))  // Cast strlen to int
            {
                if (!check_space_surroundings(map, i, j, height))
                    return (0);
            }
            else if (map[i][j] == '0' || is_player_char(map[i][j]))
            {
                if (!check_floor_surroundings(map, i, j, height))
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int check_floor_surroundings(char **map, int y, int x, int height)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int i = 0;
    int new_y, new_x;
    
    while (i < 4)
    {
        new_y = y + directions[i][0];
        new_x = x + directions[i][1];
        if (new_y < 0 || new_y >= height)
            return (0);
        if (new_x < 0 || new_x >= (int)strlen(map[new_y]))  // Cast strlen to int
            return (0);
        if (map[new_y][new_x] == ' ')
            return (0);
        i++;
    }
    return (1);
}

int check_space_surroundings(char **map, int y, int x, int height)
{
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int i = 0;
    int new_y, new_x;
    
    while (i < 4)
    {
        new_y = y + directions[i][0];
        new_x = x + directions[i][1];
        if (new_y >= 0 && new_y < height && new_x >= 0)
        {
            if (new_x < (int)strlen(map[new_y]))  // Cast strlen to int
            {
                if (map[new_y][new_x] != '1' && map[new_y][new_x] != ' ')
                    return (0);
            }
        }
        i++;
    }
    return (1);
}

int is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
