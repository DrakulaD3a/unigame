#include "timer.h"
#include <stdbool.h>
#include <time.h>

Timer timerCreate(time_t duration, bool repeating) {
    Timer timer;
    timer.start = time(NULL);
    timer.duration = duration;
    timer.repeating = repeating;
    return timer;
}

bool timerHasEnded(Timer *timer) {
    time_t current_time = time(NULL);
    if (timer->start + timer->duration < current_time) {
        if (timer->repeating) {
            timer->start = current_time;
        }
        return true;
    }
    return false;
}
