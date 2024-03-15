#pragma once

#include <stdbool.h>
#include <time.h>

typedef struct {
    time_t start;
    time_t duration;

    bool repeating;
} Timer;

Timer timerCreate(time_t duration, bool repeating);

bool timerHasEnded(Timer *timer);
