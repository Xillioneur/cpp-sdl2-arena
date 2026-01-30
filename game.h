#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include "player.h"
#include "enemy.h"
#include "utils.h"
#include <vector>

class Game {
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Player player;
    std::vector<Enemy> enemies;
    bool game_over = false;
    bool title_screen = true;
    int frame = 0;

    void init();
    void start_new_run();
    void handle_input();
    void update_sword_animation();
    void update();
    void draw_sword(float hilt_x, float hilt_y, float sword_angle);
    void draw_player();
    void render();
    void run();
};

#endif