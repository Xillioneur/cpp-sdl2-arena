#include "utils.h"
#include "constants.h"

void thick_line(SDL_Renderer* r, int x1, int y1, int x2, int y2, int thick) {
    if (thick <= 1) {
        SDL_RenderDrawLine(r, x1, y1, x2, y2);
        return;
    }
    int dx = x2 - x1, dy = y2 - y1;
    float len = std::hypot(static_cast<float>(dx), static_cast<float>(dy));
    if (len < 1.0f) return;
    float nx = -dy / len, ny = dx / len;
    for (int t = -thick/2; t <= thick/2; t++) {
        int ox = static_cast<int>(nx * t + 0.5f), oy = static_cast<int>(ny * t + 0.5f);
        SDL_RenderDrawLine(r, x1 + ox, y1 + oy, x2 + ox, y2 + oy);
    }
}

void outline_circle(SDL_Renderer* r, int cx, int cy, int radius, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    if (radius < 1) return;
    SDL_SetRenderDrawColor(r, red, green, blue, alpha);
    for (int i = 0; i < 360; i += 8) {
        float rad = i * PI / 180.0f;
        float x = static_cast<int>(cx + radius * cos(rad) * 0.5f);
        float y = static_cast<int>(cy + radius * sin(rad) * 0.5f);
        SDL_RenderDrawPoint(r, x, y);
    }
}