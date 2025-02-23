#include "../inc/game.h"

int key_press(int keycode, t_player *player) {
    if(keycode == W) player->key_up = true;
    if(keycode == S) player->key_down = true;
    if(keycode == A) player->key_left = true;
    if(keycode == D) player->key_right = true;
    if(keycode == LEFT) player->left_rotate = true;
    if(keycode == RIGHT) player->right_rotate = true;
    return 0;
}

int key_release(int keycode, t_player *player) {
    if(keycode == W) player->key_up = false;
    if(keycode == S) player->key_down = false;
    if(keycode == A) player->key_left = false;
    if(keycode == D) player->key_right = false;
    if(keycode == LEFT) player->left_rotate = false;
    if(keycode == RIGHT) player->right_rotate = false;
    return 0;
}

void move_player(t_player *player) {
    float speed = 3.0;
    float rotSpeed = 0.05;
    float moveStep = speed * cos(player->angle);
    float strafeStep = speed * sin(player->angle);

    if(player->left_rotate) player->angle -= rotSpeed;
    if(player->right_rotate) player->angle += rotSpeed;
    if(player->angle > 2*PI) player->angle -= 2*PI;
    if(player->angle < 0) player->angle += 2*PI;

    if(player->key_up) {
        player->x += cos(player->angle) * speed;
        player->y += sin(player->angle) * speed;
    }
    if(player->key_down) {
        player->x -= cos(player->angle) * speed;
        player->y -= sin(player->angle) * speed;
    }
    if(player->key_left) {
        player->x += strafeStep;
        player->y -= moveStep;
    }
    if(player->key_right) {
        player->x -= strafeStep;
        player->y += moveStep;
    }
}
