#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include "player.h"
#include "utils.h"

class Game {
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Player player;
    int frame = 0;

    void init();
    void start_new_run();
    void handle_input();
    void update();
    void draw_player();
    void render();
    void run();
};

#endif