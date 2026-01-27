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
    start_new_run();
}

void Game::start_new_run() {
    player = Player();
    frame = 0;
}

void Game::handle_input() {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) exit(0);
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    Vector2 move(0, 0);
    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) move.y -= 1;
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) move.y += 1;
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) move.x -= 1;
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) move.x += 1;
    
    // TODO: Add roll_timer
    if (move.magnitude() > 0) {
        move = move.normalized() * PLAYER_SPEED;
        player.pos = player.pos + move;
    }
}

void Game::update() {
    handle_input();
}

void Game::draw_player() {
    float cx = WINDOW_W / 2.0f;
    float cy = WINDOW_H / 2.0f;

    SDL_SetRenderDrawColor(renderer, 0, 240, 255, 160);
    outline_circle(renderer, static_cast<int>(cx), static_cast<int>(cy), PLAYER_SIZE + 25, 0, 240, 255, 160);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int grid_size_x = 105;
    int grid_size_y = 85;
    int offset_x = static_cast<int>(player.pos.x) % grid_size_x;
    int offset_y = static_cast<int>(player.pos.y) % grid_size_y;

    SDL_SetRenderDrawColor(renderer, 0, 100, 160, 40);
    for (int i = -15; i < 20; ++i) {
        int sx = i * grid_size_x - offset_x + (frame % grid_size_y);
        thick_line(renderer, sx, 0, sx, WINDOW_H, 3);
    }

    draw_player();

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