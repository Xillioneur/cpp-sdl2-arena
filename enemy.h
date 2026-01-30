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
};

#endif