#include "utils.h"
#include "constants.h"

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