#pragma once

#include "../utils.h"
#include <SDL2/SDL.h>
#include "player.h"
#include "enemy.h"


typedef enum {
    FIREBALL = 1,
    ICEBLAST = 2,
    MAGIC_KNIFE = 3,
} ProjectileTypes;

typedef struct {
    SDL_FRect shell;
    SDL_FPoint coords;
    SDL_FPoint destination;
    float speed;

    SDL_Texture *texture;
} Projectile;

Projectile spawnProjectileP(Player *player, ProjectileTypes *type, SDL_Texture *texture);

Projectile spawnProjectileE(Enemy *enemy, ProjectileTypes *type, SDL_Texture *texture);

void moveProjectile(Projectile *projectile);