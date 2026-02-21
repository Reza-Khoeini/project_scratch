#include "globals.h"

// SDL globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

// Application state
bool gRunning = true;
bool gProgramRunning = false;

// Project state
ProjectState gProject;
int gSelectedSprite = 0;
int gSelectedSound = -1;
int gMasterVolume = 100;

// UI state
int gMouseX = 0;
int gMouseY = 0;
bool gMouseDown = false;

// Event state - Section 7
bool gGreenFlagPressed = false;
char gLastKeyPressed = '\0';
char gLastBroadcast[MAX_NAME_LEN] = "";
