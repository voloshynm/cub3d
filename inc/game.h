#ifndef GAME_H
#define GAME_H

// Add X11 headers for Linux compatibility
#include <X11/X.h>
#include <X11/keysym.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define DEBUG 0

// Updated Linux keycodes
# define W XK_w
# define A XK_a
# define S XK_s
# define D XK_d
# define LEFT XK_Left
# define RIGHT XK_Right

# define PI 3.14159265359
# define FLOOR_COLOR 0x808080
# define CEILING_COLOR 0x87CEEB

#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct s_player {
    float x;
    float y;
    float angle;
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool left_rotate;
    bool right_rotate;
} t_player;

typedef struct s_game {
    void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
    
    void *tex_north;
    void *tex_east;
    void *tex_south;
    void *tex_west;    
    char *tex_north_data;
    char *tex_east_data;
    char *tex_south_data;
    char *tex_west_data;
    char *tex_data;
    int tex_width;
    int tex_height;
    int tex_bpp;
    int tex_size_line;
    int tex_endian;
    
    t_player player;
    char **map;
    int map_width;
    int map_height;
} t_game;

// Function declarations
void init_player(t_player *player);
int key_release(int keycode, t_player *player);
int key_press(int keycode, t_player *player);
void move_player(t_player *player);
void init_game(t_game *game);
int draw_loop(t_game *game);
void clear_image(t_game *game);
void put_pixel(int x, int y, int color, t_game *game);
void load_textures(t_game *game);
void cast_ray(t_game *game, float rayAngle, int x);
void draw_textured_wall(t_game *game, int x, int side, int texX, float lineHeight);
bool touch_wall(float x, float y, t_game *game);


#endif
