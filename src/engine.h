#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

bool InitSDL();

void DeinitSDL();

bool CreateWindow(const char *title, int width, int height);

void StartLoop(void (*update)(float), void (*render)(float));

void ExitGame();

bool IsKeyDown(SDL_Scancode key);

bool IsKeyUp(SDL_Scancode key);

bool IsKeyReleased(SDL_Scancode key);

bool IsKeyPressed(SDL_Scancode key);

void GetMousePosition(int *x, int *y);

bool IsMouseButtonPressed(int button);
