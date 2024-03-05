#include "engine.h"
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void update(float dt);
void render(float dt);

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

void update(float dt) {}

void render(float dt) {}
