#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef SDL_FPoint Screen;

SDL_FPoint CoordsToSDL(SDL_FPoint coords, Screen screen);

void SetCoordsToSDL(SDL_FPoint coords, Screen screen, SDL_FRect *shell);

// ==============================================================================

bool InitSDL();

void DeinitSDL();

bool CreateWindow(const char *title, int width, int height);

void StartLoop(void (*update)(float, SDL_Window *),
               void (*render)(float, SDL_Renderer *));

void ExitGame();

bool IsKeyDown(SDL_Scancode key);

bool IsKeyUp(SDL_Scancode key);

bool IsKeyReleased(SDL_Scancode key);

bool IsKeyPressed(SDL_Scancode key);

void GetMousePosition(int *x, int *y);

bool IsMouseButtonPressed(int button);

SDL_Texture *LoadTexture(const char *path);
