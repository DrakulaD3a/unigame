#include "utils.h"
#include <math.h>
#include <stdbool.h>

SDL_FPoint CoordsToSDL(SDL_FPoint coords, Screen screen) {
    // TODO: Bounds checking
    SDL_FPoint result;
    result.x = coords.x - screen.x;
    result.y = coords.y - screen.y;
    return result;
}

void SetCoordsToSDL(SDL_FPoint coords, Screen screen, SDL_FRect *shell) {
    shell->x = (int)CoordsToSDL(coords, screen).x;
    shell->y = (int)CoordsToSDL(coords, screen).y;
}

SDL_FPoint normalizeVector(SDL_FPoint vector) {
    float scale = sqrt(1 / (vector.x * vector.x + vector.y * vector.y));
    SDL_FPoint result = {
        .x = vector.x * scale,
        .y = vector.y * scale,
    };
    return result;
}

bool HasIntersectionF(const SDL_FRect *A, const SDL_FRect *B) {
    float Amin, Amax, Bmin, Bmax;

    if (!A || !B) {
        return false;
    }

    Amin = A->x;
    Amax = Amin + A->w;
    Bmin = B->x;
    Bmax = Bmin + B->w;
    if (Bmin > Amin)
        Amin = Bmin;
    if (Bmax < Amax)
        Amax = Bmax;
    if (Amax <= Amin)
        return false;

    Amin = A->y;
    Amax = Amin + A->h;
    Bmin = B->y;
    Bmax = Bmin + B->h;
    if (Bmin > Amin)
        Amin = Bmin;
    if (Bmax < Amax)
        Amax = Bmax;
    if (Amax <= Amin)
        return false;

    return true;
}

Direction DirectionFromVector(SDL_FPoint vector) {
    if (vector.x > 0) {
        if (vector.y > 0) {
            if (vector.x > vector.y) {
                return RIGHT;
            } else {
                return DOWN;
            }
        } else {
            if (vector.x > -vector.y) {
                return RIGHT;
            } else {
                return UP;
            }
        }
    } else {
        if (vector.y > 0) {
            if (-vector.x > vector.y) {
                return LEFT;
            } else {
                return DOWN;
            }
        } else {
            if (-vector.x > -vector.y) {
                return LEFT;
            } else {
                return UP;
            }
        }
    }
}
