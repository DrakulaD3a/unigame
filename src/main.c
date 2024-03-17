#include "engine/engine.h"
#include "entities/enemy.h"
#include "entities/player.h"
#include "timer.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// TODO: Make this depend on time
#define MAX_ENEMIES 10

void update(float dt, SDL_Window *window);
void render(float dt, SDL_Renderer *renderer);

Screen screen = {0.0, 0.0};
Player player = {
    .shell = {50, 50, 64, 64},
    .coords = {50.0, 50.0},
    .hp = 100,
    .speed = 250.0,
};
Enemy enemies[MAX_ENEMIES];
int enemiesCount = 0;
SDL_Texture *enemyTexture;

Timer spawnTimer;

int main() {
    if (!InitSDL()) {
        return 1;
    }

    if (!CreateWindow("Unigame", SCREEN_WIDTH, SCREEN_HEIGHT)) {
        return 1;
    }

    srand(time(NULL));

    spawnTimer = timerCreate(5, true);
    player.texture = LoadTexture("assets/Bob.png");
    enemyTexture = LoadTexture("assets/Dero.png");
    StartLoop(update, render);

    DeinitSDL();

    return 0;
}

void update(float dt, SDL_Window *window) {
    handlePlayerMovement(&player, &screen, dt);

    if (IsKeyDown(SDL_SCANCODE_ESCAPE)) {
        ExitGame();
    }

    if (timerHasEnded(&spawnTimer)) {
        if (enemiesCount < MAX_ENEMIES) {
            enemies[enemiesCount] = spawnEnemy(&player, window, enemyTexture);
            enemiesCount++;
        }
    }
    for (int i = 0; i < enemiesCount; i++) {
        moveEnemy(&enemies[i], &player, dt);
        SetCoordsToSDL(enemies[i].coords, screen, &enemies[i].shell);
    }

    for (int i = 0; i < enemiesCount; i++) {
        if (HasIntersectionF(&player.shell, &enemies[i].shell)) {
            player.hp -= 5;
            deleteEnemy(enemies, enemiesCount, i);
            enemiesCount--;
            break;
        }
    }
    if (player.hp <= 0) {
        ExitGame();
    }
}

void render(float dt, SDL_Renderer *renderer) {
    // Clearing the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Rendering player
    SDL_RenderCopyF(renderer, player.texture, NULL, &player.shell);

    // Rendering enemies
    for (int i = 0; i < enemiesCount; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRectF(renderer, &enemies[i].shell);
        SDL_RenderCopyF(renderer, enemies[i].texture, NULL, &enemies[i].shell);
    }
}
