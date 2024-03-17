#pragma once

#include "../engine/engine.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_FRect shell;
    SDL_FPoint coords;
    int hp;
    float speed;

    SDL_Texture *texture;
} Player;

// dir: w - up, s - down, a - left, d - right
void handlePlayerMovement(Player *player, Screen *screen, float dt);

void attack(Player *player);
