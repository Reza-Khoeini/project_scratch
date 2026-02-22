#ifndef TYPES_H
#define TYPES_H

#include <SDL2/SDL_mixer.h>

// Constants
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define MAX_SPRITES 10
#define MAX_SOUNDS 10
#define MAX_NAME_LEN 64

// Sprite structure - Section 15
typedef struct {
    char name[MAX_NAME_LEN];
    double x;
    double y;
    double direction;
    double size;
    bool visible;
    bool active;
} Sprite;

// Sound structure - Sections 6, 18
typedef struct {
    char name[MAX_NAME_LEN];
    Mix_Chunk* chunk;
    int volume;
    bool muted;
    bool active;
} Sound;

// Event types - Section 7
typedef enum {
    EVENT_NONE = 0,
    EVENT_GREEN_FLAG,
    EVENT_KEY_PRESSED,
    EVENT_SPRITE_CLICKED,
    EVENT_BROADCAST_RECEIVED
} EventType;

// Event structure
typedef struct {
    EventType type;
    int keyCode;
    char broadcastName[MAX_NAME_LEN];
} Event;

// Project state for Save/Load - Section 1
typedef struct {
    Sprite sprites[MAX_SPRITES];
    int spriteCount;
    Sound sounds[MAX_SOUNDS];
    int soundCount;
    char projectName[MAX_NAME_LEN];
} ProjectState;

#endif
