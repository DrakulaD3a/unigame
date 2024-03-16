#include "enemy.h"
#include "player.h"
#include <SDL2/SDL_video.h>
#include <stdlib.h>

#define ENEMY_WIDTH 20.
#define ENEMY_HEIGHT 20.
#define ENEMY_SPAWN_DIS_MIN 350.

// FIXME: Set the distance to player instead of using the window size
// We don't want the game to be pay to win(bigger monitor == enemies spawning
// further away)
Enemy spawnEnemy(Player *player , SDL_Window *window) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    short side = rand() % 4;

    short dis_offset = rand() % 100;

    Coords coords;

    switch (side) {
    // NORTH
    case 0:
        coords.x = player->coords.x + rand() % w - ENEMY_WIDTH / 2.;
        coords.y = player->coords.y - ENEMY_HEIGHT - ENEMY_SPAWN_DIS_MIN + dis_offset;
        break;

    // EAST
    case 1:
        coords.x = player->coords.x + w + ENEMY_WIDTH + ENEMY_SPAWN_DIS_MIN + dis_offset;
        coords.y = player->coords.y + rand() % h - ENEMY_HEIGHT / 2.;
        break;

    // SOUTH
    case 2:
        coords.x = player->coords.x + rand() % w - ENEMY_WIDTH / 2.;
        coords.y = player->coords.y + h + ENEMY_SPAWN_DIS_MIN + dis_offset;
        break;

    // WEST
    case 3:
        coords.x = player->coords.x - ENEMY_WIDTH - ENEMY_SPAWN_DIS_MIN + dis_offset;
        coords.y = player->coords.y + rand() % h - ENEMY_HEIGHT / 2.;
        break;
    }

    Enemy enemy = {
        .shell = {.x = coords.x,
                  .y = coords.y,
                  .w = ENEMY_WIDTH,
                  .h = ENEMY_HEIGHT},
        .coords = coords,
        .hp = 100,
        .speed = 5.0,
    };
    return enemy;
}
