#include "engine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
static const Uint8 *keyStates = NULL;
static Uint8 lastKeyStates[SDL_NUM_SCANCODES];
static bool isRunning = true;

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

bool InitSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "IMG_Init failed: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF_Init failed: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
        fprintf(stderr,
                "SDL_SetHint of SDL_HINT_RENDER_SCALE_QUALITY failed: %s\n",
                SDL_GetError());
    }

    return true;
}

void DeinitSDL() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool CreateWindow(const char *title, int width, int height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);

    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return false;
    }

    if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0) {
        fprintf(stderr, "SDL_SetRenderDrawBlendMode failed: %s\n",
                SDL_GetError());
        return false;
    }

    keyStates = SDL_GetKeyboardState(NULL);
    memset(lastKeyStates, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);

    return true;
}

void StartLoop(void (*update)(float, SDL_Window *),
               void (*render)(float, SDL_Renderer *)) {
    double time = 0.;
    const double dt = 1. / 60.;
    double currentTime = SDL_GetTicks() / 1000.;
    double accumulator = 0.;

    while (isRunning) {
        memcpy(lastKeyStates, keyStates, sizeof(Uint8) * SDL_NUM_SCANCODES);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
                return;
            }
        }

        double newTime = SDL_GetTicks64() / 1000.;
        double frameTime = newTime - currentTime;
        if (frameTime > 0.25) {
            frameTime = 0.25;
        }
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) {
            update((float)dt, window);
            time += dt;
            accumulator -= dt;
        }

        if (!isRunning) {
            break;
        }

        render((float)accumulator / dt, renderer);
        SDL_RenderPresent(renderer);
    }
}

void ExitGame() { isRunning = false; }

bool IsKeyDown(SDL_Scancode key) { return keyStates[key]; }

bool IsKeyUp(SDL_Scancode key) { return !IsKeyDown(key); }

bool IsKeyReleased(SDL_Scancode key) {
    return !IsKeyDown(key) && lastKeyStates[key];
}

bool IsKeyPressed(SDL_Scancode key) {
    return IsKeyDown(key) && !lastKeyStates[key];
}

void GetMousePosition(int *x, int *y) { SDL_GetMouseState(x, y); }

bool IsMouseButtonPressed(int button) {
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
}

SDL_Texture *LoadTexture(const char *path) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    if (!texture) {
        fprintf(stderr, "IMG_LoadTexture failed: %s\n", IMG_GetError());
    }
    return texture;
}
