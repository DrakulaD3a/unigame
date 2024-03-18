#include "projectile.h"
#include "../engine/engine.h"
#include <SDL2/SDL.h>

Projectile spawnProjectileP(Player *player, ProjectileTypes *type,
                            SDL_Texture *texture) {
    int x, y;
    GetMousePosition(&x, &y);

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
        .destination =
            {
                .x = x,
                .y = y,
            },
        .texture = texture,
    };

    return projectile;
}

Projectile spawnProjectileE(Enemy *enemy, ProjectileTypes *type,
                            SDL_Texture *texture) {
    int x, y;
    GetMousePosition(&x, &y);

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
        .destination =
            {
                .x = x,
                .y = y,
            },
        .texture = texture,
    };

    return projectile;
}
