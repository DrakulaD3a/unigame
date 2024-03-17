#include "enemy.h"
#include "../utils.h"
#include "player.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

#define ENEMY_WIDTH 64.
#define ENEMY_HEIGHT 64.
#define ENEMY_SPEED 185.0 + (rand() % 30)
#define ENEMY_SPAWN_DIS_MIN 350.

Enemy spawnEnemy(Player *player, SDL_Window *window, SDL_Texture *texture) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    short side = rand() % 4;

    short dis_offset = rand() % 100;

    SDL_FPoint coords;

    switch (side) {
    // NORTH
    case 0:
        coords.x = player->coords.x + rand() % w - ENEMY_WIDTH / 2.;
        coords.y =
            player->coords.y - ENEMY_HEIGHT - ENEMY_SPAWN_DIS_MIN + dis_offset;
        break;

    // EAST
    case 1:
        coords.x =
            player->coords.x + ENEMY_WIDTH + ENEMY_SPAWN_DIS_MIN + dis_offset;
        coords.y = player->coords.y + rand() % h - ENEMY_HEIGHT / 2.;
        break;

    // SOUTH
    case 2:
        coords.x = player->coords.x + rand() % w - ENEMY_WIDTH / 2.;
        coords.y = player->coords.y + ENEMY_SPAWN_DIS_MIN + dis_offset;
        break;

    // WEST
    case 3:
        coords.x =
            player->coords.x - ENEMY_WIDTH - ENEMY_SPAWN_DIS_MIN + dis_offset;
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
        .speed = ENEMY_SPEED,
        .direction = DOWN,
        .texture = texture,
    };
    return enemy;
}

void moveEnemy(Enemy *enemy, Player *player, float dt) {
    // HACK: Don't ask me why it works as it works, I don't know
    SDL_FPoint direction = {
        .x = enemy->coords.x - player->coords.x,
        .y = player->coords.y - enemy->coords.y,
    };
    SDL_FPoint normal = normalizeVector(direction);

    enemy->direction = DirectionFromVector(direction);
    enemy->coords.x -= normal.x * enemy->speed * dt;
    enemy->coords.y += normal.y * enemy->speed * dt;
}

void deleteEnemy(Enemy enemy[], int enemiesCount, int index) {
    for (int i = index; i < enemiesCount; i++) {
        enemy[i] = enemy[i + 1];
    }
}
