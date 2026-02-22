#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "types.h"

// SDL globals
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

// Application state
extern bool gRunning;
extern bool gProgramRunning;

// Project state
extern ProjectState gProject;
extern int gSelectedSprite;
extern int gSelectedSound;
extern int gMasterVolume;

// UI state
extern int gMouseX;
extern int gMouseY;
extern bool gMouseDown;

// Event state - Section 7
extern bool gGreenFlagPressed;
extern char gLastKeyPressed;
extern char gLastBroadcast[MAX_NAME_LEN];

#endif
