#include "../inc/game.h"

char **get_map(void) {
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "10000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return map;
}

void init_player(t_player *player) {
    player->x = 2.5f * BLOCK;  // Spawn away from edges
    player->y = 2.5f * BLOCK;
    player->angle = PI / 2;  // Start facing north
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
    player->left_rotate = false;
    player->right_rotate = false;
}

void init_game(t_game *game) {
    init_player(&game->player);
    game->map = get_map();
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Assam & Max's Game");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    load_textures(game);
}

int draw_loop(t_game *game) {
    t_player *p = &game->player;
    move_player(p);
    clear_image(game);
    
    float fov = PI / 3;
    float rayAngle = p->angle - fov / 2;
    float angleStep = fov / WIDTH;

    for(int x = 0; x < WIDTH; x++) {
        cast_ray(game, rayAngle, x);
        rayAngle += angleStep;
    }
    
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

int main(void) {
    t_game game;
    init_game(&game);
    
    mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
    mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
    mlx_loop_hook(game.mlx, draw_loop, &game);
    
    mlx_loop(game.mlx);
    return 0;
}
