
#include "projectile.h"
#include "../engine/engine.h"
#include "../utils.h"
#include <SDL2/SDL.h>

Projectile spawnProjectileP(Player *player, ProjectileTypes *type, SDL_Texture *texture)
{
    Projectile projectile;
    int x;
    int y;

    projectile.shell.x = player->shell.x;
    projectile.shell.y = player->shell.y;
    projectile.shell.w = 8;
    projectile.shell.h = 16;

    projectile.coords.x = player->coords.x;
    projectile.coords.y = player->coords.y;

    GetMousePosition(&x, &y);
    projectile.destination.x = x;
    projectile.destination.y = y;

    projectile.texture = texture;

    return projectile;
}

Projectile spawnProjectileE(Enemy *enemy, ProjectileTypes *type, SDL_Texture *texture)
{
    Projectile projectile;
    int x;
    int y;

    projectile.shell.x = enemy->shell.x;
    projectile.shell.y = enemy->shell.y;
    projectile.shell.w = 8;
    projectile.shell.h = 16;

    projectile.coords.x = enemy->coords.x;
    projectile.coords.y = enemy->coords.y;

    GetMousePosition(&x, &y);
    projectile.destination.x = x;
    projectile.destination.y = y;

    projectile.texture = texture;

    return projectile;
}
