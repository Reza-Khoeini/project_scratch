#include "sprite.h"
#include "globals.h"
#include <cstdio>
#include <cstring>

int addSprite(const char* name, double x, double y) {
    if (gProject.spriteCount >= MAX_SPRITES) {
        printf("Error: Maximum sprite count reached\n");
        return -1;
    }
    
    int idx = gProject.spriteCount;
    Sprite* s = &gProject.sprites[idx];
    
    strncpy(s->name, name, MAX_NAME_LEN - 1);
    s->name[MAX_NAME_LEN - 1] = '\0';
    s->x = x;
    s->y = y;
    s->direction = 90.0;
    s->size = 100.0;
    s->visible = true;
    s->active = true;
    
    gProject.spriteCount++;
    printf("Sprite '%s' added at (%.1f, %.1f)\n", name, x, y);
    return idx;
}

void removeSprite(int index) {
    if (index < 0 || index >= gProject.spriteCount) return;
    
    printf("Sprite '%s' removed\n", gProject.sprites[index].name);
    
    for (int i = index; i < gProject.spriteCount - 1; i++) {
        gProject.sprites[i] = gProject.sprites[i + 1];
    }
    gProject.spriteCount--;
    
    if (gSelectedSprite >= gProject.spriteCount) {
        gSelectedSprite = gProject.spriteCount - 1;
    }
}

void setSpritePosition(int index, double x, double y) {
    if (index < 0 || index >= gProject.spriteCount) return;
    
    if (x < -240) x = -240;
    if (x > 240) x = 240;
    if (y < -180) y = -180;
    if (y > 180) y = 180;
    
    gProject.sprites[index].x = x;
    gProject.sprites[index].y = y;
}

void setSpriteSize(int index, double size) {
    if (index < 0 || index >= gProject.spriteCount) return;
    if (size < 1) size = 1;
    if (size > 500) size = 500;
    gProject.sprites[index].size = size;
}

void setSpriteDirection(int index, double direction) {
    if (index < 0 || index >= gProject.spriteCount) return;
    while (direction < 0) direction += 360;
    while (direction >= 360) direction -= 360;
    gProject.sprites[index].direction = direction;
}

void setSpriteVisible(int index, bool visible) {
    if (index < 0 || index >= gProject.spriteCount) return;
    gProject.sprites[index].visible = visible;
}

void renameSprite(int index, const char* newName) {
    if (index < 0 || index >= gProject.spriteCount) return;
    strncpy(gProject.sprites[index].name, newName, MAX_NAME_LEN - 1);
    gProject.sprites[index].name[MAX_NAME_LEN - 1] = '\0';
}
