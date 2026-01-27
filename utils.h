#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

void thick_line(SDL_Renderer* r, int x1, int y1, int x2, int y2, int thick);
void outline_circle(SDL_Renderer* r, int cx, int cy, int radius, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255);

#endif