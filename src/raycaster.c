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

void draw_textured_wall(t_game *game, int x, int side, int texX, float lineHeight) {
    int drawStart = (HEIGHT - lineHeight) / 2;
    int drawEnd = (HEIGHT + lineHeight) / 2;
    
    // Select correct texture based on wall orientation
    char *tex_data;
    if (side == 0) { // East/West walls
        tex_data = (game->player.angle > PI/2 && game->player.angle < 3*PI/2) 
                 ? game->tex_west_data : game->tex_east_data;
    } else { // North/South walls
        tex_data = (game->player.angle > PI) 
                 ? game->tex_south_data : game->tex_north_data;
    }

    float texStep = (float)TEX_HEIGHT / lineHeight;
    float texPos = (drawStart - HEIGHT/2 + lineHeight/2) * texStep;

    for(int y = drawStart; y < drawEnd; y++) {
        int texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += texStep;
        
        // Critical safety check
        if(texX >= 0 && texX < TEX_WIDTH && texY >= 0 && texY < TEX_HEIGHT) {
            int color = *(int*)(tex_data + 
                (texY * game->tex_size_line + texX * (game->tex_bpp/8)));
            put_pixel(x, y, color, game);
        }
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
    
    // Calculate world position for proper texture wrapping
    float wallX;
    if(side == 0) {
        wallX = game->player.y + perpWallDist * rayDirY;
    } else {
        wallX = game->player.x + perpWallDist * rayDirX;
    }
    
    // Full texture coordinate calculation with wrapping
    wallX = fmod(wallX, BLOCK) / BLOCK;  // Wrap every 64 pixels
    int texX = (int)(wallX * TEX_WIDTH);

    draw_textured_wall(game, x, side, texX, lineHeight);
}
