#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"

class Player {
public:
    Vector2 pos;

    float sword_relative_angle = -PI / 6.0f;

    float lagged_aim_angle = 0.0f;


    Player() {
        pos = Vector2(WINDOW_W / 2, WINDOW_H / 2);
    }
};

#endif