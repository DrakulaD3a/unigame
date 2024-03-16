#pragma once

#include "../engine/engine.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_FRect shell;
    Coords coords;
    int hp;
    float speed;

    SDL_Texture *texture;
} Player;

// dir: w - up, s - down, a - left, d - right
void playerMove(Player *player, char dir);

void attack(Player *player);
