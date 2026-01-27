#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

#define WINDOW_W 1200
#define WINDOW_H 900

struct Vector2 {
    float x, y;
    Vector2(float px = 0, float py = 0) : x(px), y(py) {}
};

#endif