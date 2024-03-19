#include "engine/engine.h"
#include "entities/enemy.h"
#include "entities/player.h"
#include "entities/projectile.h"
#include "timer.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

// TODO: Make this depend on time
#define MAX_ENEMIES 10

#define MAX_PROJECTILES 1

void update(float dt, SDL_Window *window);
void render(float dt, SDL_Renderer *renderer);

Screen screen = {0.0, 0.0};
Player player = {
    .shell = {SCREEN_WIDTH / 2. - 32., SCREEN_HEIGHT / 2. - 32., 64, 64},
    .coords = {SCREEN_WIDTH / 2. - 32., SCREEN_HEIGHT / 2. - 32.},
    .hp = 100,
    .speed = 250.0,
    .direction = DOWN,
};
Enemy enemies[MAX_ENEMIES];
int enemiesCount = 0;
SDL_Texture *enemyTexture;

Projectile projectiles[MAX_PROJECTILES];
int projectileCount = 0;
SDL_Texture *firebalTexture;

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
    firebalTexture = LoadTexture("assets/Fireball.png");
    StartLoop(update, render);

    DeinitSDL();

    return 0;
}

void update(float dt, SDL_Window *window) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    if (player.shell.x != w / 2. || player.shell.y != w / 2.) {
        screen.x = player.coords.x - w / 2. + player.shell.w / 2.;
        screen.y = player.coords.y - h / 2. + player.shell.h / 2.;
    }

    handlePlayerMovement(&player, &screen, dt);

    if (IsKeyDown(SDL_SCANCODE_ESCAPE)) {
        ExitGame();
    }

    if (IsKeyDown(SDL_SCANCODE_SPACE)) {
        if (projectileCount < MAX_PROJECTILES) {
            projectiles[projectileCount] =
                spawnProjectileP(&player, FIREBALL, firebalTexture, &screen);
            projectileCount++;
        }
    }

    if (timerHasEnded(&spawnTimer)) {
        if (enemiesCount < MAX_ENEMIES) {
            enemies[enemiesCount] = spawnEnemy(&player, window, enemyTexture);
            enemiesCount++;
        }
    }
    for (int i = 0; i < enemiesCount; i++) {
        moveEnemy(&enemies[i], &player, dt);
        SetCoordsToSDL(enemies[i].coords, &screen, &enemies[i].shell);
    }

    for (int i = 0; i < projectileCount; i++) {
        moveProjectile(&projectiles[i], dt);
        SetCoordsToSDL(projectiles[i].coords, &screen, &projectiles[i].shell);
    }

    for (int i = 0; i < projectileCount; i++) {
        if (projectiles[i].distanceTraveled > 500) {

            deleteProjectile(projectiles, projectileCount, i);
            projectileCount--;
        }
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
    SDL_Rect drawRect = {
        .x = 0,
        .y = 0,
        .w = 32,
        .h = 32,
    };

    // Clearing the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Rendering player
    drawRect.x = player.direction;
    SDL_RenderCopyF(renderer, player.texture, &drawRect, &player.shell);

    // Rendering enemies
    for (int i = 0; i < enemiesCount; i++) {
        drawRect.x = enemies[i].direction;
        SDL_RenderCopyF(renderer, enemies[i].texture, &drawRect,
                        &enemies[i].shell);
    }

    for (int i = 0; i < projectileCount; i++) {
        SDL_RenderCopyF(renderer, projectiles[i].texture, NULL,
                        &projectiles[i].shell);
    }
}
