#include "enemy.h"

Enemy::Enemy(Vector2 p, int t, int wave_equiv) : pos(p), type(t) {
    float wave_scale = 1.0f + (wave_equiv - 1) * 0.15f;
    health = max_health = (90.0f + t * 70.0f + static_cast<float>(rand() % 100)) * wave_scale;
}

void Enemy::update(const Vector2& player_pos, int frame) {
    Vector2 to_player = player_pos - pos;
    float dist = to_player.magnitude();
    Vector2 dir = to_player.normalized();
    angle = atan2(to_player.y, to_player.x);

    pos = pos + dir * speed;
}