#include "player.h"
#include "../engine/engine.h"
#include "../utils.h"
#include <SDL2/SDL.h>

void handlePlayerMovement(Player *player, Screen *screen, float dt) {
    SDL_FPoint direction = {
        .x = 0.,
        .y = 0.,
    };

    if (IsKeyDown(SDL_SCANCODE_W)) {
        direction.y -= 1;
    }
    if (IsKeyDown(SDL_SCANCODE_S)) {
        direction.y += 1;
    }
    if (IsKeyDown(SDL_SCANCODE_A)) {
        direction.x -= 1;
    }
    if (IsKeyDown(SDL_SCANCODE_D)) {
        direction.x += 1;
    }

    if (direction.x != 0. || direction.y != 0.) {
        SDL_FPoint normal = normalizeVector(direction);
        player->direction = DirectionFromVector(direction);
        player->coords.x += normal.x * player->speed * dt;
        player->coords.y += normal.y * player->speed * dt;
    }

    SetCoordsToSDL(player->coords, *screen, &player->shell);
}
