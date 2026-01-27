#include "game.h"
#include <iostream>

void Game::init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Neon Aether Blade", 
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_W, WINDOW_H, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    SDL_ShowCursor(SDL_ENABLE);
}

void Game::handle_input() {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) exit(0);
    }
}

void Game::update() {
    handle_input();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Game::run() {
    init();
    while (true) {
        update();
        render();
        SDL_Delay(16);
    }
}