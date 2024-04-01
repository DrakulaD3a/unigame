#pragma once

#include "enemy.h"
#include "player.h"
#include <SDL2/SDL.h>

typedef enum {
    FIREBALL = 0,
    ICEBLAST = 1,
    MAGIC_KNIFE = 2,
} ProjectileTypes;

typedef struct {
    SDL_FRect shell;
    SDL_FPoint coords;
    SDL_FPoint direction;
    float distanceTraveled;
    float speed;
    bool reachedDest;
    int damage;

    SDL_Texture *texture;
} Projectile;

Projectile spawnProjectileP(Player *player, ProjectileTypes type,
                            SDL_Texture *texture, Screen *screen);

Projectile spawnProjectileE(Enemy *enemy, ProjectileTypes type,
                            SDL_Texture *texture, Screen *screen);

void moveProjectile(Projectile *projectile, float dt);

void deleteProjectile(Projectile projectiles[], int projectileCount, int index);
