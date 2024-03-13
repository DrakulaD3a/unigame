#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    double x;
    double y;
} Coords;

SDL_FPoint CoordsToSDL(Coords coords, Coords screen);

void SetCoordsToSDL(Coords coords, Coords screen, SDL_FRect *shell);

// ==============================================================================

bool InitSDL();

void DeinitSDL();

bool CreateWindow(const char *title, int width, int height);

void StartLoop(void (*update)(float), void (*render)(float, SDL_Renderer *));

void ExitGame();

bool IsKeyDown(SDL_Scancode key);

bool IsKeyUp(SDL_Scancode key);

bool IsKeyReleased(SDL_Scancode key);

bool IsKeyPressed(SDL_Scancode key);

void GetMousePosition(int *x, int *y);

bool IsMouseButtonPressed(int button);
