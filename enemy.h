#ifndef ENEMY_H
#define ENEMY_H

#include "constants.h"

class Enemy {
public:
    Vector2 pos;
    float health = 20.0f;
    float max_health = 20.0f;
    float speed = 2.2f;
    int type = 0;
    float death_timer = 0.0f;
    float angle = 0.0f;
    bool active = true;

    Enemy(Vector2 p, int t, int wave_equiv);
    void update(const Vector2& player_pos, int frame);
};

#endif