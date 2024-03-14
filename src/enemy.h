#pragma once
#include "engine.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_FRect shell;
    Coords coords;
    int hp;
    float speed;
} Enemy;

Enemy spawnEnemy(Screen screen, SDL_Window *window);
