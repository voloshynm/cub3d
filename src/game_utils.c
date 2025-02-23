#include "../inc/game.h"

void put_pixel(int x, int y, int color, t_game *game)
{
    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    
    int index = y * game->size_line + x * (game->bpp / 8);
    *(unsigned int*)(game->data + index) = mlx_get_color_value(game->mlx, color);
}


void clear_image(t_game *game) {
    for(int y = 0; y < HEIGHT; y++) {
        u_int32_t color = (y < HEIGHT/2) ? CEILING_COLOR : FLOOR_COLOR;
        for(int x = 0; x < WIDTH; x++) {
            put_pixel(x, y, color, game);
        }
    }
}

float distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool touch_wall(float x, float y, t_game *game) {
    int gridX = (int)x / BLOCK;
    int gridY = (int)y / BLOCK;
    return game->map[gridY][gridX] == '1';
}
