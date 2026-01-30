#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"

class Player {
public:
    Vector2 pos;
    float stamina = 100.0f;
    float max_stamina = 100.0f;
    float stamina_regen = 30.0f;

    SwordState sword_state = SwordState::Rest;    
    float sword_timer = 0.0f;
    float sword_relative_angle = -PI / 6.0f;
    float charge_time = 0.0f;
    bool is_heavy_attack = false;


    float current_windup_time = 0.0f;
    float current_swing_time = 0.0f;
    float current_recovery_time = 0.0f;
    float current_lunge_speed = 0.0f;

    float attack_speed_factor = 1.0f;

    float lagged_aim_angle = 0.0f;

    int combo_count = 0;

    Player() {
        pos = Vector2(WINDOW_W / 2, WINDOW_H / 2);
    }
};

#endif