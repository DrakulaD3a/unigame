#pragma once
#include "../engine/engine.h"
#include "player.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_FRect shell;
    SDL_FPoint coords;
    int hp;
    float speed;

    SDL_Texture *texture;
} Enemy;

Enemy spawnEnemy(Player *player, SDL_Window *window, SDL_Texture *texture);

void moveEnemy(Enemy *enemy, Player *player);

void deleteEnemy(Enemy enemy[], int enemiesCount, int index);
