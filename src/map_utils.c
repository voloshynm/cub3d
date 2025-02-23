#include "../inc/game.h"
#include <string.h>

void validate_map(t_game *game) {
    int height = 0;
    int width = 0;
    
    while(game->map[height]) {
        int current_width = strlen(game->map[height]);
        if(height == 0) width = current_width;
        if(current_width != width) {
            fprintf(stderr, "Map is not rectangular!\n");
            exit(1);
        }
        height++;
    }
    game->map_width = width;
    game->map_height = height;
}

void find_valid_spawn(t_player *player, t_game *game) {
    for(int y = 1; y < game->map_height-1; y++) {
        for(int x = 1; x < game->map_width-1; x++) {
            if(game->map[y][x] == '0') {
                player->x = (x + 0.5f) * BLOCK;
                player->y = (y + 0.5f) * BLOCK;
                return;
            }
        }
    }
    fprintf(stderr, "No valid spawn found!\n");
    exit(1);
}

bool check_collision(t_game *game, float new_x, float new_y) {
    int grid_x = new_x / BLOCK;
    int grid_y = new_y / BLOCK;
    
    if(grid_x < 0 || grid_x >= game->map_width) return true;
    if(grid_y < 0 || grid_y >= game->map_height) return true;
    
    // Check current cell and adjacent cells
    for(int y = -1; y <= 1; y++) {
        for(int x = -1; x <= 1; x++) {
            int check_x = grid_x + x;
            int check_y = grid_y + y;
            if(check_x >= 0 && check_x < game->map_width &&
               check_y >= 0 && check_y < game->map_height) {
                if(game->map[check_y][check_x] == '1') {
                    float dx = fabs(new_x - (check_x * BLOCK));
                    float dy = fabs(new_y - (check_y * BLOCK));
                    if(dx < 10.0f && dy < 10.0f) return true;
                }
            }
        }
    }
    return false;
}

