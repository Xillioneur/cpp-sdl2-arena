#ifndef ENEMY_H
#define ENEMY_H

#include "constants.h"

class Enemy {
public:
    Vector2 pos;
    float speed = 2.2f;
    int type = 0;
    float angle = 0.0f;
    bool active = true;

    Enemy(Vector2 p, int t, int wave_equiv);
    void update(const Vector2& player_pos, int frame);
};

#endif