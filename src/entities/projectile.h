#pragma once

#include "enemy.h"
#include "player.h"
#include <SDL2/SDL.h>

typedef enum {
    FIREBALL = 1,
    ICEBLAST = 2,
    MAGIC_KNIFE = 3,
} ProjectileTypes;

typedef struct {
    SDL_FRect shell;
    SDL_FPoint coords;
    SDL_FPoint direction;
    float distanceTraveled;
    float speed;
    bool reachedDest;

    SDL_Texture *texture;
} Projectile;

Projectile spawnProjectileP(Player *player, ProjectileTypes type,
                            SDL_Texture *texture, Screen *screen);

Projectile spawnProjectileE(Enemy *enemy, ProjectileTypes type,
                            SDL_Texture *texture, Screen *screen);

void moveProjectile(Projectile *projectile, float dt);

void deleteProjectile(Projectile projectiles[], int projectileCount, int index);
