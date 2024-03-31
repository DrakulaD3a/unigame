#include "projectile.h"
#include "../engine/engine.h"
#include <SDL2/SDL.h>

Projectile spawnProjectileP(Player *player, ProjectileTypes type,
                            SDL_Texture *texture, Screen *screen) {
    int x, y;
    GetMousePosition(&x, &y);

    SDL_FPoint direction = {
        .x = x - player->coords.x,
        .y = y - player->coords.y,
    };

    direction = SDLToCoords(direction, screen);

    SDL_FPoint normal = normalizeVector(direction);

    Projectile projectile = {
        .shell =
            {
                .x = player->shell.x,
                .y = player->shell.y,
                .w = 8,
                .h = 16,
            },
        .coords =
            {
                .x = player->coords.x,
                .y = player->coords.y,
            },
        .direction = normal,
        .texture = texture,
    };

    switch (type)
    {
    case FIREBALL:
        projectile.speed = 500;
        break;
    case ICEBLAST:
        projectile.speed = 450;
        break;
    case MAGIC_KNIFE:
        projectile.speed = 850;
        break;
    
    default:
        break;
    }

    switch (type)
    {
    case FIREBALL:
        projectile.damage = 50;
        break;
    case ICEBLAST:
        projectile.damage = 40;
        break;
    case MAGIC_KNIFE:
        projectile.damage = 35;
        break;
    
    default:
        break;
    }

    return projectile;
}

Projectile spawnProjectileE(Enemy *enemy, ProjectileTypes type,
                            SDL_Texture *texture, Screen *screen) {
    int x, y;
    GetMousePosition(&x, &y);

    SDL_FPoint direction = {
        .x = x - enemy->coords.x,
        .y = y - enemy->coords.y,
    };

    direction = SDLToCoords(direction, screen);

    SDL_FPoint normal = normalizeVector(direction);

    Projectile projectile = {
        .shell =
            {
                .x = enemy->shell.x,
                .y = enemy->shell.y,
                .w = 8,
                .h = 16,
            },
        .coords =
            {
                .x = enemy->coords.x,
                .y = enemy->coords.y,
            },
        .direction = normal,
        .speed = 500,
        .texture = texture,
    };

    return projectile;
}

void moveProjectile(Projectile *projectile, float dt) {
    projectile->coords.y += projectile->direction.y * projectile->speed * dt;
    projectile->coords.x += projectile->direction.x * projectile->speed * dt;
    projectile->distanceTraveled += projectile->speed * dt;
}

void deleteProjectile(Projectile projectiles[], int projectileCount,
                      int index) {
    for (int i = index; i < projectileCount; i++) {
        projectiles[i] = projectiles[i + 1];
    }
}