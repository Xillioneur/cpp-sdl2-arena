#include "enemy.h"

Enemy::Enemy(Vector2 p, int t, int wave_equiv) : pos(p), type(t) {}

void Enemy::update(const Vector2& player_pos, int frame) {
    Vector2 to_player = player_pos - pos;
    float dist = to_player.magnitude();
    Vector2 dir = to_player.normalized();
    angle = atan2(to_player.y, to_player.x);

    pos = pos + dir * speed;
}