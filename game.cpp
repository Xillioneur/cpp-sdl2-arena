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

    int mx, my;
    Uint32 mouse = SDL_GetMouseState(&mx, &my);
    static bool was_left_down = false;
    bool left_down = mouse & SDL_BUTTON(SDL_BUTTON_LEFT);
    bool left_pressed = left_down && !was_left_down;

    if (!title_screen && !game_over) { 
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

        if (left_pressed && player.stamina >= 28.0f &&
            (player.sword_state == SwordState::Rest || player.sword_state == SwordState::Recovery)) {
                player.sword_state = SwordState::Charging;
        }

        if (player.sword_state == SwordState::Charging && !left_down && was_left_down) {
            bool heavy = player.charge_time >= 18.0f;
            float cost = heavy ? 45.0f : 28.0f;
            if (player.stamina >= cost) {
                player.stamina -= cost;
                player.is_heavy_attack = heavy;

                if (!heavy && player.sword_timer > 0.0f) {
                    player.combo_count = std::min(4, player.combo_count + 1);
                } else {
                    player.combo_count = 0;
                }

                float asf = player.attack_speed_factor;

                float base_windup = heavy ? 28.0f : 10.0f;
                float base_swing = heavy ? 18.0 : 10.0f;
                float base_recovery = heavy ? 40.0f : 22.0f;

                float combo_speed = heavy ? 1.0f : (1.0f - 0.18f * player.combo_count);

                player.current_windup_time = base_windup * combo_speed * asf;
                player.current_swing_time = base_swing * (heavy ? 1.0f : combo_speed * 1.1f) * asf;
                player.current_recovery_time = base_recovery * combo_speed * asf;

                // TODO: Mult

                player.sword_state = SwordState::Windup;
                player.sword_timer - player.current_windup_time;
            } else {
                player.sword_state = SwordState::Rest;
            }
        }
    }

    if ((title_screen || game_over) && left_pressed) {
        if (title_screen) {
            title_screen = false;
        } else {
            start_new_run();
        }
    }

    was_left_down = left_down;
}

void Game::update_sword_animation() {
    float rest_relative = -PI / 6.0f;

    float base_back = player.is_heavy_attack ? PI / 1.8f : PI / 4.0f;
    float back_bonus = 0.2f * PI * player.combo_count;
    float max_back = base_back + back_bonus;

    float base_arc = player.is_heavy_attack ? PI * 2.4f : PI * 1.6f;
    float arc_bonus = 0.5f * PI * player.combo_count;
    float swing_arc = base_arc + arc_bonus;

    if (player.sword_state == SwordState::Charging) {
        float t = std::min(1.0f, player.charge_time / 30.0f);
        player.sword_relative_angle = rest_relative - t * max_back;
    } else if (player.sword_state == SwordState::Windup) {
        float t = (player.current_windup_time - player.sword_timer) / player.current_windup_time;
        player.sword_relative_angle = rest_relative - t * max_back;
    } else if (player.sword_state == SwordState::Swing) {
        float t = (player.current_swing_time - player.sword_timer) / player.current_swing_time;
        player.sword_relative_angle = rest_relative - max_back + t * swing_arc;
    } else if (player.sword_state == SwordState::Recovery) {
        float t = (player.current_recovery_time - player.sword_timer) / player.current_recovery_time;
        player.sword_relative_angle = rest_relative - max_back + swing_arc - t * swing_arc;
    } else {
        player.sword_relative_angle = rest_relative;
    }
}


void Game::update() {
    if (title_screen || game_over) {
        handle_input();
        frame++;
        return;
    }

    handle_input();

    int mx, my;
    SDL_GetMouseState(&mx, &my);
    float target_aim = atan2(my - WINDOW_H / 2.0f, mx - WINDOW_W / 2.0f);

    float follow_speed = 0.28f;
    if (player.sword_state == SwordState::Rest) follow_speed = 0.35f;
    else if (player.sword_state == SwordState::Recovery) follow_speed = 0.22f;
    else if (player.sword_state == SwordState::Charging) follow_speed = 0.40f;
    else if (player.sword_state == SwordState::Windup) follow_speed = 0.18f;
    else if (player.sword_state == SwordState::Swing) follow_speed = player.is_heavy_attack ? 0.12f : 0.20f - 0.02f * player.combo_count;

    float diff = atan2(sin(target_aim - player.lagged_aim_angle), cos(target_aim - player.lagged_aim_angle));
    player.lagged_aim_angle += diff * follow_speed;

    player.stamina = std::min(player.max_stamina, player.stamina + player.stamina_regen / 60.0f);

    if (player.sword_state == SwordState::Windup || player.sword_state == SwordState::Swing || player.sword_state == SwordState::Recovery) {
        player.sword_timer -= 1.0f;
        if (player.sword_timer <= 0.0f) {
            if (player.sword_state == SwordState::Windup) {
                player.sword_state = SwordState::Swing;
                player.sword_timer = player.current_swing_time;
            } else if (player.sword_state == SwordState::Swing) {
                player.sword_state = SwordState::Recovery;
                player.sword_timer = player.current_recovery_time;
            } else if (player.sword_state == SwordState::Recovery) {
                player.sword_state = SwordState::Rest;
                player.is_heavy_attack = false;
                player.combo_count = 0;
            }
        }
    }

    update_sword_animation();

}

void Game::draw_sword(float hilt_x, float hilt_y, float sword_angle) {
    Vector2 tip(hilt_x + cos(sword_angle) * SWORD_LENGTH, hilt_y + sin(sword_angle) * SWORD_LENGTH);    

    // TODO: Glow
    SDL_SetRenderDrawColor(renderer, 120, 255, 255, 255);
    thick_line(renderer, static_cast<int>(hilt_x), static_cast<int>(hilt_y),
                static_cast<int>(tip.x), static_cast<int>(tip.y), 20);

    // TODO: Finish sword
}

void Game::draw_player() {
    float cx = WINDOW_W / 2.0f;
    float cy = WINDOW_H / 2.0f;

    SDL_SetRenderDrawColor(renderer, 0, 240, 255, 160);
    outline_circle(renderer, static_cast<int>(cx), static_cast<int>(cy), PLAYER_SIZE + 25, 0, 240, 255, 160);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    outline_circle(renderer, static_cast<int>(cx), static_cast<int>(cy), PLAYER_SIZE, 0, 255, 255, 255);

    Vector2 hilt_base(cx + cos(player.lagged_aim_angle) * PLAYER_SIZE * 0.8f, cy + sin(player.lagged_aim_angle) * PLAYER_SIZE * 0.7f);
    float sword_angle = player.lagged_aim_angle + player.sword_relative_angle;

    draw_sword(hilt_base.x, hilt_base.y, sword_angle);
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
    for (int i = -15; i < 20; ++i) {
        int sy = i * grid_size_y - offset_y + (frame % grid_size_y);
        thick_line(renderer, 0, sy, WINDOW_W, sy, 3);
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