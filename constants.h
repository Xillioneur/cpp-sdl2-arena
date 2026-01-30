#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>
#include <cmath>

#define WINDOW_W 1200
#define WINDOW_H 900
#define PI 3.14159265f
#define PLAYER_SIZE 40
#define PLAYER_SPEED 5.5f
#define SWORD_LENGTH 150.0f

struct Vector2 {
    float x, y;
    Vector2(float px = 0, float py = 0) : x(px), y(py) {}
    Vector2 operator+(const Vector2& o) const { return Vector2(x + o.x, y + o.y); }
    Vector2 operator*(float s) const { return Vector2(x * s, y * s); }
    float magnitude() const { return std::hypot(x, y); }
    Vector2 normalized() const {
        float m = magnitude();
        return m > 0 ? Vector2(x / m, y / m) : Vector2();
    }
    float dot(const Vector2& o) const { return x * o.x + y * o.y; }
};

enum class SwordState { Rest, Charging, Windup, Swing, Recovery };

struct SpawnIndicator {
    Vector2 pos;
    float timer = 90.0f;
    int type = 0;
};

#endif