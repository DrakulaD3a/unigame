#include "engine.h"
#include "player.h"
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void update(float dt);
void render(float dt, SDL_Renderer *renderer);

Player player = {
    .shell = {50, 50, 20, 20},
    .coords = {50.0, 50.0},
    .hp = 100,
    .speed = 5.0,
};

int main() {

    if (!InitSDL()) {
        return 1;
    }

    if (!CreateWindow("Unigame", SCREEN_WIDTH, SCREEN_HEIGHT)) {
        return 1;
    }

    StartLoop(update, render);

    DeinitSDL();

    return 0;
}

void update(float dt) {
    if (IsKeyDown(SDL_SCANCODE_W)) {
        playerMove(&player, 'w');
    }
    if (IsKeyDown(SDL_SCANCODE_S)) {
        playerMove(&player, 's');
    }
    if (IsKeyDown(SDL_SCANCODE_A)) {
        playerMove(&player, 'a');
    }
    if (IsKeyDown(SDL_SCANCODE_D)) {
        playerMove(&player, 'd');
    }

    player.shell.x = player.coords.x;
    player.shell.y = player.coords.y;
}

void render(float dt, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRectF(renderer, &player.shell);
}
