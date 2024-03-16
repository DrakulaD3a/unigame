#include "utils.h"
#include <math.h>

SDL_FPoint normalizeVector(SDL_FPoint vector) {
    float scale = sqrt(1 / (vector.x * vector.x + vector.y * vector.y));
    SDL_FPoint result = {
        .x = vector.x * scale,
        .y = vector.y * scale,
    };
    return result;
}
