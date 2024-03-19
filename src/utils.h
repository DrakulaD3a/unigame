#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef SDL_FPoint Screen;

SDL_FPoint CoordsToSDL(SDL_FPoint coords, Screen *screen);

SDL_FPoint SDLToCoords(SDL_FPoint coords, Screen *screen);

void SetCoordsToSDL(SDL_FPoint coords, Screen *screen, SDL_FRect *shell);

SDL_FPoint normalizeVector(SDL_FPoint vector);

bool HasIntersectionF(const SDL_FRect *A, const SDL_FRect *B);

typedef enum { RIGHT = 0, UP = 32, LEFT = 2 * 32, DOWN = 3 * 32 } Direction;

Direction DirectionFromVector(SDL_FPoint vector);
