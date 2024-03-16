#pragma once
#include "../engine/engine.h"
#include "player.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_FRect shell;
    Coords coords;
    int hp;
    float speed;
} Enemy;

Enemy spawnEnemy(Player *player, SDL_Window *window);

void moveEnemy(Enemy *enemy, Player *player);

SDL_FPoint normalizeVector(SDL_FPoint vector);
