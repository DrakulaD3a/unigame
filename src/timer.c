#include "timer.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

Timer timerCreate(double duration, bool repeating) {
    Timer timer = {
        .start = SDL_GetTicks64() / 1000.,
        .duration = duration,
        .repeating = repeating,
    };
    return timer;
}

bool timerHasEnded(Timer *timer) {
    double current_time = SDL_GetTicks64() / 1000.;
    if (timer->start + timer->duration < current_time) {
        if (timer->repeating) {
            timer->start = current_time;
        }
        return true;
    }
    return false;
}
