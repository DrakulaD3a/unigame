#include "engine/engine.h"
#include "entities/player.h"
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void update(float dt);
void render(float dt, SDL_Renderer *renderer);

Screen screen = {0.0, 0.0};
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
}

void render(float dt, SDL_Renderer *renderer) {
    // Clearing the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Rendering player
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRectF(renderer, &player.shell);
}
