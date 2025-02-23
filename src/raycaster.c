#include "../inc/game.h"

void load_textures(t_game *game) {
    game->tex_north = mlx_xpm_file_to_image(game->mlx, "./inc/tex/w_north.xpm", 
        &game->tex_width, &game->tex_height);
    game->tex_east = mlx_xpm_file_to_image(game->mlx, "./inc/tex/w_east.xpm", 
        &game->tex_width, &game->tex_height);
    game->tex_south = mlx_xpm_file_to_image(game->mlx, "./inc/tex/w_south.xpm", 
        &game->tex_width, &game->tex_height);
    game->tex_west = mlx_xpm_file_to_image(game->mlx, "./inc/tex/w_west.xpm", 
        &game->tex_width, &game->tex_height);

    if (!game->tex_north || !game->tex_east || !game->tex_south || !game->tex_west) {
        fprintf(stderr, "Error loading textures\n");
        exit(1);
    }

    game->tex_north_data = mlx_get_data_addr(game->tex_north, &game->tex_bpp,
        &game->tex_size_line, &game->tex_endian);
    game->tex_east_data = mlx_get_data_addr(game->tex_east, &game->tex_bpp,
        &game->tex_size_line, &game->tex_endian);
    game->tex_south_data = mlx_get_data_addr(game->tex_south, &game->tex_bpp,
        &game->tex_size_line, &game->tex_endian);
    game->tex_west_data = mlx_get_data_addr(game->tex_west, &game->tex_bpp,
        &game->tex_size_line, &game->tex_endian);
}

void draw_textured_wall(t_game *game, int x, int side, int step, float wallX, float lineHeight) {
    int drawStart = (HEIGHT - lineHeight) / 2;
    int drawEnd = (HEIGHT + lineHeight) / 2;
    int texX = (int)(wallX * (float)TEX_WIDTH);
    char *tex_data;

    // Determine which texture to use
    if (side == 0) { // East/West walls
        tex_data = (step > 0) ? game->tex_east_data : game->tex_west_data;
    } else { // North/South walls
        tex_data = (step > 0) ? game->tex_south_data : game->tex_north_data;
    }

    for(int y = drawStart; y < drawEnd; y++) {
        int texY = (y - drawStart) * TEX_HEIGHT / lineHeight;
        int color = *(int*)(tex_data + (texY * game->tex_size_line + texX * (game->tex_bpp/8)));
        put_pixel(x, y, color, game);
    }
}

void cast_ray(t_game *game, float rayAngle, int x) {
    float rayDirX = cos(rayAngle);
    float rayDirY = sin(rayAngle);
    
    // DDA algorithm implementation
    float sideDistX, sideDistY;
    float deltaDistX = fabs(1 / rayDirX);
    float deltaDistY = fabs(1 / rayDirY);
    float perpWallDist;
    
    int mapX = (int)game->player.x / BLOCK;
    int mapY = (int)game->player.y / BLOCK;
    int stepX, stepY;
    int hit = 0;
    int side;

    // Calculate step and initial sideDist
    if(rayDirX < 0) {
        stepX = -1;
        sideDistX = (game->player.x - mapX * BLOCK) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = ((mapX + 1) * BLOCK - game->player.x) * deltaDistX;
    }
    if(rayDirY < 0) {
        stepY = -1;
        sideDistY = (game->player.y - mapY * BLOCK) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = ((mapY + 1) * BLOCK - game->player.y) * deltaDistY;
    }

    // DDA loop
    while(!hit) {
        if(sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if(game->map[mapY][mapX] == '1') hit = 1;
    }

    // Calculate distance and line height
    if(side == 0)
        perpWallDist = (mapX * BLOCK - game->player.x + (1 - stepX) * BLOCK / 2) / rayDirX;
    else
        perpWallDist = (mapY * BLOCK - game->player.y + (1 - stepY) * BLOCK / 2) / rayDirY;
    
    float lineHeight = (BLOCK / perpWallDist) * HEIGHT;
    float wallX = side == 0 ? 
        game->player.y + perpWallDist * rayDirY : 
        game->player.x + perpWallDist * rayDirX;
    wallX -= (int)wallX;

    if(side == 0) {
        draw_textured_wall(game, x, side, stepX, wallX, lineHeight);
    } else {
        draw_textured_wall(game, x, side, stepY, wallX, lineHeight);
    }
}
