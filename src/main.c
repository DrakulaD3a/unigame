#include "engine/engine.h"
#include "entities/enemy.h"
#include "entities/player.h"
#include "timer.h"
#include <SDL2/SDL_render.h>
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
    .shell = {50, 50, 20, 20},
    .coords = {50.0, 50.0},
    .hp = 100,
    .speed = 5.0,
};
Enemy enemies[MAX_ENEMIES];
int enemiesCount = 0;
Timer spawnTimer;

int main() {
    if (!InitSDL()) {
        return 1;
    }

    if (!CreateWindow("Unigame", SCREEN_WIDTH, SCREEN_HEIGHT)) {
        return 1;
    }

    srand(time(NULL));

    spawnTimer = timerCreate(10, true);
    player.texture = LoadTexture("assets/Bob.png");

    StartLoop(update, render);

    DeinitSDL();

    return 0;
}

void update(float dt, SDL_Window *window) {
    if (IsKeyDown(SDL_SCANCODE_W)) {
        playerMove(&player, 'w');
        SetCoordsToSDL(player.coords, screen, &player.shell);
    }
    if (IsKeyDown(SDL_SCANCODE_S)) {
        playerMove(&player, 's');
        SetCoordsToSDL(player.coords, screen, &player.shell);
    }
    if (IsKeyDown(SDL_SCANCODE_A)) {
        playerMove(&player, 'a');
        SetCoordsToSDL(player.coords, screen, &player.shell);
    }
    if (IsKeyDown(SDL_SCANCODE_D)) {
        playerMove(&player, 'd');
        SetCoordsToSDL(player.coords, screen, &player.shell);
    }
    if (IsKeyDown(SDL_SCANCODE_ESCAPE)) {
        ExitGame();
    }

    if (timerHasEnded(&spawnTimer)) {
        if (enemiesCount < MAX_ENEMIES) {
            enemies[enemiesCount] = spawnEnemy(&player, window);
            enemiesCount++;
        }
    }
}

void render(float dt, SDL_Renderer *renderer) {
    // Clearing the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Rendering player
    SDL_RenderCopyF(renderer, player.texture, NULL, &player.shell);
}
