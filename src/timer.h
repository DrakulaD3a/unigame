#pragma once

#include <stdbool.h>

typedef struct {
    double start;
    double duration;

    bool repeating;
} Timer;

Timer timerCreate(double duration, bool repeating);

bool timerHasEnded(Timer *timer);
