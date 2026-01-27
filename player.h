#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"

class Player {
public:
    Vector2 pos;

    Player() {
        pos = Vector2(WINDOW_W / 2, WINDOW_H / 2);
    }
};

#endif