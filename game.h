#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include "utils.h"

class Game {
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    void init();
    void handle_input();
    void update();
    void render();
    void run();
};

#endif