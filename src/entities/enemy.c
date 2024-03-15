#include "enemy.h"
#include <SDL2/SDL_video.h>
#include <stdlib.h>

#define ENEMY_WIDTH 20.
#define ENEMY_HEIGHT 20.

// FIXME: Set the distance to player instead of using the window size
// We don't want the game to be pay to win(bigger monitor == enemies spawning
// further away)
Enemy spawnEnemy(Screen screen, SDL_Window *window) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    short side = rand() % 4;

    Coords coords;

    switch (side) {
    // NORTH
    case 0:
        coords.x = screen.x + rand() % w - ENEMY_WIDTH / 2.;
        coords.y = screen.y - ENEMY_HEIGHT - 10.;
        break;

    // EAST
    case 1:
        coords.x = screen.x + w + ENEMY_WIDTH + 10.;
        coords.y = screen.y + rand() % h - ENEMY_HEIGHT / 2.;
        break;

    // SOUTH
    case 2:
        coords.x = screen.x + rand() % w - ENEMY_WIDTH / 2.;
        coords.y = screen.y + h + 10.;
        break;

    // WEST
    case 3:
        coords.x = screen.x - ENEMY_WIDTH - 10.;
        coords.y = screen.y + rand() % h - ENEMY_HEIGHT / 2.;
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
